#include <stdexcept>
#include "sprite_batch.h"

#include <algorithm>

namespace zombies {
    Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const Color &color) :
            texture(Texture),
            depth(Depth) {

        topLeft.color = color;
        topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

        bottomLeft.color = color;
        bottomLeft.setPosition(destRect.x, destRect.y);
        bottomLeft.setUV(uvRect.x, uvRect.y);

        bottomRight.color = color;
        bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
        bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

        topRight.color = color;
        topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }

    Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const Color &color,
                 float angle) :
            texture(Texture),
            depth(Depth) {

        glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

        // Get points centered at origin
        glm::vec2 tl(-halfDims.x, halfDims.y);
        glm::vec2 bl(-halfDims.x, -halfDims.y);
        glm::vec2 br(halfDims.x, -halfDims.y);
        glm::vec2 tr(halfDims.x, halfDims.y);

        // Rotate the points
        tl = rotatePoint(tl, angle) + halfDims;
        bl = rotatePoint(bl, angle) + halfDims;
        br = rotatePoint(br, angle) + halfDims;
        tr = rotatePoint(tr, angle) + halfDims;

        topLeft.color = color;
        topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
        topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

        bottomLeft.color = color;
        bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
        bottomLeft.setUV(uvRect.x, uvRect.y);

        bottomRight.color = color;
        bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
        bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

        topRight.color = color;
        topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
        topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
    }

    glm::vec2 Glyph::rotatePoint(const glm::vec2 &pos, float angle) {
        glm::vec2 newv;
        newv.x = pos.x * cos(angle) - pos.y * sin(angle);
        newv.y = pos.x * sin(angle) + pos.y * cos(angle);
        return newv;
    }

    SpriteBatch::SpriteBatch() : VBO(0), VAO(0) {
    }

    SpriteBatch::~SpriteBatch() {
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }

        if (VBO != 0) {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
    }

    void SpriteBatch::init() {
        createVertexArray();
    }

    void SpriteBatch::draw(Texture *texture, glm::vec2 position, const Color &color) {
        glyphs.emplace_back(
                glm::vec4(position.x, position.y, texture->getWidth(), texture->getHeight()),
                glm::vec4(0, 0, 1, 1),
                texture->getGLTexture(),
                0,
                color
        );
    }

    void SpriteBatch::draw(Texture *texture, const glm::vec4 &destinationRectangle, const Color &color) {
        glyphs.emplace_back(
                destinationRectangle,
                glm::vec4(0, 0, 1, 1),
                texture->getGLTexture(),
                0,
                color
        );
    }

    void SpriteBatch::draw(Texture *texture, const glm::vec4 &destinationRectangle, const glm::vec4 &sourceRectangle,
                           const Color &color, float depth, float angle) {
        glyphs.emplace_back(destinationRectangle, sourceRectangle, texture->getGLTexture(), depth, color, angle);
    }

    void SpriteBatch::draw(Texture *texture, const glm::vec4 &destinationRectangle, const glm::vec4 &sourceRectangle,
                           const Color &color, float depth, glm::vec2 direction) {
        const glm::vec2 right(1.0f, 0.0f);
        float angle = acos(glm::dot(right, direction));
        if (direction.y < 0.0f) {
            angle = -angle;
        }

        glyphs.emplace_back(destinationRectangle, sourceRectangle, texture->getGLTexture(), depth, color, angle);
    }

    void SpriteBatch::begin(GlyphSortOrder sortType /* Default - GlyphSortType::TEXTURE */) {
        if (batchingInProgress) {
            throw std::runtime_error("You have to end the batch by calling 'end()' before calling 'begin()' again.");
        }

        batchingInProgress = true;

        currentSortType = sortType;
        renderBatches.clear();

        // Makes _glyphs.size() == 0, however it does not free internal memory.
        // So when we later call emplace_back it doesn't need to internally call new.
        glyphs.clear();
    }

    void SpriteBatch::end() {
        if (!batchingInProgress) {
            throw std::runtime_error("You have to start the batch by calling 'begin()' before calling 'end()'.");
        }

        // Set up all pointers for fast sorting
        glyphPointers.resize(glyphs.size());
        for (size_t i = 0; i < glyphs.size(); i++) {
            glyphPointers[i] = &glyphs[i];
        }

        sortGlyphs();
        createRenderBatches();

        renderBatch();
        batchingInProgress = false;
    }

    void SpriteBatch::renderBatch() {
        if (activeRenderTarget != nullptr) {
            activeRenderTarget->bind();
        } else {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        glBindVertexArray(VAO);

        for (size_t i = 0; i < renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
            glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].verticesCount);
        }

        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void SpriteBatch::createRenderBatches() {
        // Stores all the vertices that we need to upload
        std::vector<SpriteBatchVertex> vertices;

        // Resize the buffer to the exact size we need so we can treat
        // it like an array
        vertices.resize(glyphPointers.size() * 6);

        if (glyphPointers.empty()) {
            return;
        }

        int offset = 0;
        int cv = 0;

        // Add the first batch
        renderBatches.emplace_back(offset, 6, glyphPointers[0]->texture);
        vertices[cv++] = glyphPointers[0]->topLeft;
        vertices[cv++] = glyphPointers[0]->bottomLeft;
        vertices[cv++] = glyphPointers[0]->bottomRight;
        vertices[cv++] = glyphPointers[0]->bottomRight;
        vertices[cv++] = glyphPointers[0]->topRight;
        vertices[cv++] = glyphPointers[0]->topLeft;
        offset += 6;

        // Add all the other glyphs
        for (size_t cg = 1; cg < glyphPointers.size(); cg++) {

            // Check if this glyph can be part of the current batch
            if (glyphPointers[cg]->texture != glyphPointers[cg - 1]->texture) {
                // Make a new batch
                renderBatches.emplace_back(offset, 6, glyphPointers[cg]->texture);
            } else {
                // If its part of the current batch, just increase numVertices
                renderBatches.back().verticesCount += 6;
            }
            vertices[cv++] = glyphPointers[cg]->topLeft;
            vertices[cv++] = glyphPointers[cg]->bottomLeft;
            vertices[cv++] = glyphPointers[cg]->bottomRight;
            vertices[cv++] = glyphPointers[cg]->bottomRight;
            vertices[cv++] = glyphPointers[cg]->topRight;
            vertices[cv++] = glyphPointers[cg]->topLeft;
            offset += 6;
        }

        // Bind our VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Orphan the buffer (for speed)
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SpriteBatchVertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload the data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(SpriteBatchVertex), vertices.data());

        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SpriteBatch::createVertexArray() {
        if (VAO != 0 || VBO != 0) {
            throw std::runtime_error("skyboxVAO and VBO were already generated.");
        }

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteBatchVertex), (void *) offsetof(SpriteBatchVertex, position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SpriteBatchVertex), (void *) offsetof(SpriteBatchVertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteBatchVertex), (void *) offsetof(SpriteBatchVertex, uv));

        glBindVertexArray(0);
    }

    void SpriteBatch::sortGlyphs() {

        switch (currentSortType) {
            case GlyphSortOrder::TEXTURE:
                std::stable_sort(glyphPointers.begin(), glyphPointers.end(), [](Glyph *a, Glyph *b) -> bool {
                    return a->texture < b->texture;
                });
                break;
            case GlyphSortOrder::BACK_TO_FRONT:
                std::stable_sort(glyphPointers.begin(), glyphPointers.end(), [](Glyph *a, Glyph *b) -> bool {
                    return a->depth > b->depth;
                });
                break;
            case GlyphSortOrder::FRONT_TO_BACK:
                std::stable_sort(glyphPointers.begin(), glyphPointers.end(), [](Glyph *a, Glyph *b) -> bool {
                    return a->depth < b->depth;
                });
                break;
            case GlyphSortOrder::NONE:
                break;
        }
    }

    void SpriteBatch::setRenderTarget(TextureRenderTarget *renderTarget) {
        activeRenderTarget = renderTarget;
    }
}

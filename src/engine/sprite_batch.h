#pragma once

#include <gl.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include "texture.h"
#include "texture_render_target.h"
#include "shader.h"

namespace zombies {
    struct Position {
        float x;
        float y;
    };

    struct Color {
        Color() : r(0), g(0), b(0), a(0) {}

        constexpr Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {}

        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;

    public:
        static constexpr Color White() { return {255, 255, 255, 255}; }

        static constexpr Color Black() { return {0, 0, 0, 255}; }

        static constexpr Color Red() { return {255, 0, 0, 255}; }

        static constexpr Color Green() { return {0, 255, 0, 255}; }

        static constexpr Color Blue() { return {0, 0, 255, 255}; }
    };

    struct UV {
        float u;
        float v;
    };

    struct SpriteBatchVertex {
        Position position;

        Color color;

        UV uv;

        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }
    };

    enum GlyphSortOrder {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    class Glyph {
    public:
        Glyph() {};

        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const Color &color);

        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const Color &color,
              float angle);

        GLuint texture;
        float depth;

        SpriteBatchVertex topLeft;
        SpriteBatchVertex bottomLeft;
        SpriteBatchVertex topRight;
        SpriteBatchVertex bottomRight;

    private:
        glm::vec2 rotatePoint(const glm::vec2 &pos, float angle);
    };

    class RenderBatch {
    public:
        RenderBatch(GLuint off, GLuint vertices, GLuint tex) : offset(off),
                                                               verticesCount(vertices), texture(tex) {
        }

        GLuint offset;
        GLuint verticesCount;
        GLuint texture;
    };

    class SpriteBatch {
    public:
        SpriteBatch();

        ~SpriteBatch();

        void init();

        void draw(Texture *texture, glm::vec2 position, const Color &color);

        void draw(Texture *texture, const glm::vec4 &destinationRectangle, const Color &color);

        void draw(Texture *texture, const glm::vec4 &destinationRectangle, const glm::vec4 &sourceRectangle,
                  const Color &color, float depth = 0.0f, float angle = 0.0f);

        void draw(Texture *texture, const glm::vec4 &destinationRectangle, const glm::vec4 &sourceRectangle,
                  const Color &color, float depth = 0.0f, glm::vec2 direction = glm::vec2(0));

        void begin(GlyphSortOrder sortType = GlyphSortOrder::TEXTURE);

        void end();

        void setRenderTarget(TextureRenderTarget *renderTarget);

    private:
        void renderBatch();

        void createRenderBatches();

        void createVertexArray();

        void sortGlyphs();

        bool batchingInProgress = false;

        GLuint VBO;
        GLuint VAO;

        GlyphSortOrder currentSortType;

        // Used in sorting
        std::vector<Glyph *> glyphPointers;
        // Actual glyphs
        std::vector<Glyph> glyphs;

        std::vector<RenderBatch> renderBatches;

        TextureRenderTarget *activeRenderTarget = nullptr;
    };

}
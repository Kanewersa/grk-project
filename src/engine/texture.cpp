#include <stdexcept>
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace zombies {
    Texture::Texture(const std::string &filePath) {
        // Create OpenGL texture
        glGenTextures(1, &textureId);

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Load image data from file
        int nrChannels;

        // TODO: Fix req_comp for different image types.
        stbi_uc *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 3);

        if (!data) {
            throw std::runtime_error("Failed to load texture image: " + filePath);
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Set texture sampling parameters
        // Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Free image data as it's no longer needed
        stbi_image_free(data);
    }

    Texture::Texture(int textureWidth, int textureHeight) {
        width = textureWidth;
        height = textureHeight;

        // Create OpenGL texture
        glGenTextures(1, &textureId);

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(GLuint textureId, int textureWidth, int textureHeight) {
        width = textureWidth;
        height = textureHeight;
        this->textureId = textureId;
    }

    Texture::~Texture() {
        glDeleteTextures(1, &textureId);
    }

    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }
}
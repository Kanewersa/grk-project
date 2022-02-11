#pragma once

#include <gl.h>
#include <string>

namespace zombies {
    class Texture {
    public:
        // Creates texture from file.
        explicit Texture(const std::string& filePath);

        // Creates empty texture of given size.
        Texture(int width, int height);

        Texture(GLuint textureId, int textureWidth, int textureHeight);

        ~Texture();

        GLuint getGLTexture() const { return textureId; }

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        virtual void bind();

    protected:
        int width{};
        int height{};

    private:
        GLuint textureId{};
    };
}
#pragma once

#include "texture.h"

namespace zombies {
    class TextureRenderTarget : public Texture {
    public:
        TextureRenderTarget(int width, int height);

        ~TextureRenderTarget();

        void bind() override;

        void reallocateTexture(int width, int height);

    private:
        unsigned int FBO{};
    };
}
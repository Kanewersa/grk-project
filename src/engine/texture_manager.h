#pragma once

#include <unordered_map>
#include "texture.h"

namespace zombies {
    class TextureManager {
    public:
        static TextureManager &Instance() {
            static TextureManager instance;
            return instance;
        }

        TextureManager(TextureManager const &) = delete;

        void operator=(TextureManager const &) = delete;

        static Texture *LoadTexture(const std::string &filePath);

        static void Dispose();

    private:
        TextureManager() = default;

        std::unordered_map<std::string, Texture*> textures;
    };
}
#include "texture_manager.h"

namespace zombies {

    Texture *TextureManager::LoadTexture(const std::string &filePath) {
        if (TextureManager::Instance().textures.contains(filePath)) {
            return TextureManager::Instance().textures.at(filePath);
        }

        auto *text = new Texture(filePath);
        TextureManager::Instance().textures.insert(std::make_pair(filePath, text));

        return text;
    }

    void TextureManager::Dispose() {
        TextureManager::Instance().textures.clear();
    }
}
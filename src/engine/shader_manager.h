#pragma once

#include <unordered_map>
#include "shader.h"

namespace zombies {
    enum ShaderType {
        AnimatedModel,
        StaticModel,
        Skybox,
        Terrain,
        Bubble
    };

    class ShaderManager {
    public:
        static ShaderManager &Instance() {
            static ShaderManager instance;
            return instance;
        }

        ShaderManager(ShaderManager const &) = delete;

        void operator=(ShaderManager const &) = delete;

        static Shader &GetShader(ShaderType shaderType);

    private:
        ShaderManager();

        std::unordered_map<ShaderType, std::unique_ptr<Shader>> shaders;
    };
}

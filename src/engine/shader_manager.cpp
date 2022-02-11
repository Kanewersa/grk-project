#include "shader_manager.h"

namespace zombies {

    ShaderManager::ShaderManager() {
        shaders[ShaderType::AnimatedModel] = std::make_unique<Shader>("shaders/animated_model.vs", "shaders/animated_model.fs");
        shaders[ShaderType::StaticModel] = std::make_unique<Shader>("shaders/model.vs", "shaders/model.fs");
        shaders[ShaderType::Skybox] = std::make_unique<Shader>("shaders/skybox.vs", "shaders/skybox.fs");
        shaders[ShaderType::Terrain] = std::make_unique<Shader>("shaders/terrainShader.vs", "shaders/terrainShader.fs");
        shaders[ShaderType::Bubble] = std::make_unique<Shader>("shaders/bubbleShader.vs", "shaders/bubbleShader.fs");
    }

    Shader &ShaderManager::GetShader(ShaderType shaderType) {
        return *Instance().shaders[shaderType];
    }
}

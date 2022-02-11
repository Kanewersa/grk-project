#pragma once

#include "glm/vec3.hpp"

namespace zombies {
    struct LightingData {
        glm::vec3 color{1};
        glm::vec3 direction{0};
        glm::vec3 fogColor{0};
        float fogDensity = 0.0f;
        float fogGradient = 0.0f;
        float objectRenderDistance = 0.0f;
        int terrainRenderDistance = 0;
        bool flatTerrain = false;
    };
}

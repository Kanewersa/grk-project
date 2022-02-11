#pragma once

#include <glm/vec3.hpp>

namespace zombies {
    struct TransformComponent {
    public:
        glm::vec3 position{};
        glm::vec3 rotation{0.0f};
        glm::vec3 scale{1.0f};
    };
}
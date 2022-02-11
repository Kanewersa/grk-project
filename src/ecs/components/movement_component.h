#pragma once

#include "glm/vec3.hpp"

namespace zombies {
    struct MovementComponent {
        float speed = 1.0f;
        glm::vec3 velocity{0};
    };
}
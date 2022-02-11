#pragma once

#include "glm/vec3.hpp"

namespace zombies {
    struct FishComponent {
    public:
        glm::vec3 currentTarget;

        void getNextPos(glm::vec3 currentPos) {
            currentTarget = currentPos + glm::vec3(rand() % 100 - 60, rand() % 20 - 10, rand() % 100 - 50);
            if (currentTarget.y < 8) {
                currentTarget.y = rand() % 3 + 8;
            }
        }
    };
}
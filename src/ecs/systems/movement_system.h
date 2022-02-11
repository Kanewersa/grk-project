#pragma once

#include <entt/entt.hpp>

namespace zombies {
    class MovementSystem {
    public:
        void update(entt::registry &registry, float deltaTime);
    };
}
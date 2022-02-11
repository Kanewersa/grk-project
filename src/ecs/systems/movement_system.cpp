#include <glm/geometric.hpp>
#include "movement_system.h"
#include "../components/movement_component.h"
#include "../components/transform_component.h"
#include "../components/player_component.h"
#include "../../input_manager.h"
#include "../../utils.h"

namespace zombies {
    void MovementSystem::update(entt::registry &registry, float deltaTime) {
        auto view = registry.view<MovementComponent, TransformComponent, PlayerComponent>();
        for (auto &entity : view) {
            auto &movement = registry.get<MovementComponent>(entity);
            auto &transform = registry.get<TransformComponent>(entity);

            if (InputManager::KeyPressed(GLFW_KEY_W)) {
                movement.velocity += Utils::RotationToVector(transform.rotation.x);
            }

            if (InputManager::KeyPressed(GLFW_KEY_S)) {
                movement.velocity *= 0.9f;
            }

            if (InputManager::KeyPressed(GLFW_KEY_Q)) {
                movement.velocity -= Utils::RotationToVector(transform.rotation.x + 180.0f) * movement.speed * deltaTime;
                transform.rotation.x += 30.0f * deltaTime;
                movement.velocity += Utils::RotationToVector(transform.rotation.x) * movement.speed * deltaTime;
            }

            if (InputManager::KeyPressed(GLFW_KEY_E)) {
                movement.velocity -= Utils::RotationToVector(transform.rotation.x + 180.0f) * movement.speed * deltaTime;
                transform.rotation.x -= 30.0f * deltaTime;
                movement.velocity += Utils::RotationToVector(transform.rotation.x) * movement.speed * deltaTime;
            }

            if (InputManager::KeyPressed(GLFW_KEY_SPACE)) {
                movement.velocity += deltaTime * movement.speed * glm::vec3(0, 3, 0);
            }

            if (InputManager::KeyPressed(GLFW_KEY_LEFT_SHIFT)) {
                movement.velocity -= deltaTime * movement.speed * glm::vec3(0, 3, 0);
            }

            transform.position += movement.velocity * movement.speed * deltaTime * 0.1f;

            // Decrease velocity over time
            movement.velocity *= 0.99f;
        }
    }
}
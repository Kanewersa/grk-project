#pragma once

#include "../../camera.h"
#include "entt/entt.hpp"
#include "../components/transform_component.h"
#include "../components/bubble_component.h"
#include "../components/fish_component.h"
#include "../../window.h"
#include "../components/movement_component.h"

namespace zombies {
    class FishSystem {
    public:
        void initialize(Camera *cam, Window *win) {
            camera = cam;
            window = win;
        }

        void update(entt::registry &registry, float deltaTime) {
            auto view = registry.view<MovementComponent, TransformComponent, FishComponent>();

            for (auto &entity: view) {
                auto &movement = registry.get<MovementComponent>(entity);
                auto &transform = registry.get<TransformComponent>(entity);
                auto &fish = registry.get<FishComponent>(entity);

                if (fish.currentTarget == glm::vec3(0, 0, 0)) {
                    fish.getNextPos(transform.position);
                }

                float distance = sqrt(pow(transform.position.x - fish.currentTarget.x, 2) +
                        pow(transform.position.y - fish.currentTarget.y, 2) + pow(transform.position.z - fish.currentTarget.z, 2));
                if (distance < 0.3f) {
                    fish.getNextPos(transform.position);
                }

                glm::vec3 direction = glm::normalize(fish.currentTarget - transform.position);
                transform.position += direction * movement.speed * deltaTime;
                double yaw = atan2(direction.x, direction.z) * 180.0/3.14;
                double pitch = -atan2(direction.y, sqrt((direction.x * direction.x) + (direction.z * direction.z))) * 180.0/3.14;

                transform.rotation.x = (float)yaw;
                transform.rotation.y = (float)pitch;
            }
        }

    private:
        Window *window;
        Camera *camera;
    };
}
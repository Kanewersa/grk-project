#pragma once

#include "../../camera.h"
#include "entt/entt.hpp"
#include "../components/plant_component.h"
#include "../components/transform_component.h"
#include "../components/player_component.h"
#include "../components/bubble_component.h"

namespace zombies {
    class BubbleSystem {
    public:
        void initialize(Camera *cam, Window *win, LightingData *lighting) {
            camera = cam;
            window = win;
            lightingData = lighting;

            bubbleShader = &ShaderManager::GetShader(ShaderType::Bubble);
        }

        void update(entt::registry &registry, float deltaTime) {
            auto view = registry.view<BubbleComponent, TransformComponent>();
            for (auto &bubble: view) {
                auto &bubbleTransform = registry.get<TransformComponent>(bubble);

                bubbleTransform.position = bubbleTransform.position + (glm::vec3{0, 1, 0} +
                                           glm::vec3(0, 0.5, 0) * bubbleTransform.scale.x) * deltaTime;

                if (bubbleTransform.position.y > 50) {
                    registry.destroy(bubble);
                }
            }

            spawnTimer += deltaTime;
            if (spawnTimer <= TimerDelay) {
                return;
            }
            spawnTimer = 0.0f;

            auto view2 = registry.view<PlantComponent, TransformComponent>();

            for (auto &plant: view2) {
                // Spawn bubbles with 0.2% chance
                if (rand() % 1000 > 2) {
                    continue;
                }

                auto &plantTransform = registry.get<TransformComponent>(plant);

                auto bubble = registry.create();
                registry.emplace<BubbleComponent>(bubble, &ModelManager::GetModel(ModelType::BubbleModel));
                float scaleFactor = Utils::RandomFloat() + 0.3f;
                glm::vec3 scale = {scaleFactor, scaleFactor, 1.0f};
                registry.emplace<TransformComponent>(bubble, plantTransform.position, glm::vec3(0.0f), scale);
            }
        }

        void draw(entt::registry &registry, float deltaTime) {
            float aspectRatio = (float) window->getWidth() / (float) window->getHeight();

            glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera->getZoom()), aspectRatio,
                                                          camera->getZNear(), camera->getZFar());
            glm::mat4 viewMatrix = camera->getViewMatrix();

            bubbleShader->use();
            bubbleShader->setMatrix4("projection", projectionMatrix);
            bubbleShader->setMatrix4("view", viewMatrix);
            bubbleShader->setVector3f("fogColor", lightingData->fogColor.x, lightingData->fogColor.y,
                                      lightingData->fogColor.z);
            bubbleShader->setFloat("density", lightingData->fogDensity);
            bubbleShader->setFloat("gradient", lightingData->fogGradient);

            glm::mat4 model;

            auto view = registry.view<BubbleComponent, TransformComponent>();

            for (auto &entity: view) {
                auto &transform = registry.get<TransformComponent>(entity);

                if (glm::distance(transform.position, camera->getPosition()) > lightingData->objectRenderDistance) {
                    continue;
                }

                auto &modelComponent = registry.get<BubbleComponent>(entity);
                model = glm::mat4(1.0f);
                model = glm::translate(model, transform.position);
                glm::vec3 rotation = glm::vec4(transform.rotation, 1.0);
                model = glm::rotate(model, glm::radians(rotation.x), {0, 1, 0});
                model = glm::rotate(model, glm::radians(rotation.y), {1, 0, 0});
                model = glm::rotate(model, glm::radians(rotation.z), {0, 0, 1});
                bubbleShader->setVector3f("scale", transform.scale);
                bubbleShader->setMatrix4("model", model);
                modelComponent.model->draw(*bubbleShader);
            }
        }

    private:
        float spawnTimer;

        Window *window;
        Camera *camera;
        Shader *bubbleShader;
        LightingData *lightingData;

        const float TimerDelay = 1.0f;
    };
}
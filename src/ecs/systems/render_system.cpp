#include "render_system.h"
#include "../components/animated_model_component.h"
#include "../components/transform_component.h"
#include "../../engine/timer.h"
#include "../components/model_component.h"
#include "../components/movement_component.h"
#include "../../engine/shader_manager.h"

namespace zombies {
    RenderSystem::~RenderSystem() {
        delete animator;
        delete skybox;
        delete waterFrameBuffers;
    }

    void RenderSystem::initialize(Camera *cam, Window *win, LightingData *lighting) {
        camera = cam;
        window = win;
        lightingData = lighting;

        lightingData->direction = {0, -1 , 0};
        lightingData->fogColor = {30.0f/255.0f, 30.0f/255.0f, 85.0f/255.0f};
        lightingData->fogDensity = 0.015f;
        lightingData->fogGradient = 1.5f;
        lightingData->objectRenderDistance = 100.0f;
        lightingData->terrainRenderDistance = 3;

        waterFrameBuffers = new WaterFrameBuffers();
        waterFrameBuffers->unbindWaterFrameBuffer(win->getGLFWWindow());

        staticModelShader = &ShaderManager::GetShader(ShaderType::StaticModel);
        animatedModelShader = &ShaderManager::GetShader(ShaderType::AnimatedModel);

        animator = new Animator(nullptr);
        skybox = new class Skybox();
    }

    void RenderSystem::update(entt::registry &registry, float deltaTime) {
        staticModelShader->use();
        staticModelShader->setVector3f("lightDir", lightingData->direction);
        staticModelShader->setVector3f("lightColor", lightingData->color);

        animatedModelShader->use();
        animatedModelShader->setVector3f("lightDir", {-lightingData->direction.y, -lightingData->direction.z, lightingData->direction.x});
        animatedModelShader->setVector3f("lightColor", lightingData->color);
    }

    void RenderSystem::draw(entt::registry &registry, float deltaTime) {
        float aspectRatio = (float)window->getWidth() / (float)window->getHeight();
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera->getZoom()), aspectRatio, camera->getZNear(), camera->getZFar());
        glm::mat4 viewMatrix = camera->getViewMatrix();

        animatedModelShader->use();
        animatedModelShader->setMatrix4("projection", projectionMatrix);
        animatedModelShader->setMatrix4("view", viewMatrix);

        glm::mat4 model = glm::mat4(1.0f);

        auto view = registry.view<AnimatedModelComponent, MovementComponent, TransformComponent>();
        for (auto &entity: view) {
            auto &transform = registry.get<TransformComponent>(entity);
            auto &modelComponent = registry.get<AnimatedModelComponent>(entity);
            auto &movement = registry.get<MovementComponent>(entity);

            if (animator->getCurrentAnimation() == nullptr) {
                animator->playAnimation(&modelComponent.animation);
            }

            animator->changeAnimationSpeed(glm::length(movement.velocity/60.0f) + 0.5f);
            animator->update(deltaTime);

            auto transforms = animator->getPoseTransforms();
            for (int i = 0; i < transforms.size(); ++i) {
                std::string name = "finalBonesMatrices[" + std::to_string(i) + "]";
                animatedModelShader->setMatrix4(name.c_str(), transforms[i]);
            }

            model = glm::mat4(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::scale(model, transform.scale);
            model = glm::rotate(model, glm::radians(transform.rotation.x), {0, 1, 0});
            model = glm::rotate(model, glm::radians(transform.rotation.y), {1, 0, 0});
            model = glm::rotate(model, glm::radians(transform.rotation.z), {0, 0, 1});

            animatedModelShader->setMatrix4("model", model);
            animatedModelShader->setMatrix3("worldModel", glm::mat3(glm::transpose(glm::inverse(model))));
            modelComponent.model.draw(*animatedModelShader);
        }

        staticModelShader->use();
        staticModelShader->setMatrix4("projection", projectionMatrix);
        staticModelShader->setMatrix4("view", viewMatrix);
        staticModelShader->setVector3f("fogColor", lightingData->fogColor.x, lightingData->fogColor.y, lightingData->fogColor.z);
        staticModelShader->setFloat("density", lightingData->fogDensity);
        staticModelShader->setFloat("gradient", lightingData->fogGradient);

        auto view2 = registry.view<ModelComponent, TransformComponent>();
        for (auto &entity: view2) {
            auto &transform = registry.get<TransformComponent>(entity);
            auto &modelComponent = registry.get<ModelComponent>(entity);

            if (glm::distance(transform.position, camera->getPosition()) > lightingData->objectRenderDistance) {
                continue;
            }

            model = glm::mat4(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::scale(model, transform.scale);
            model = glm::rotate(model, glm::radians(transform.rotation.x), {0, 1, 0});
            model = glm::rotate(model, glm::radians(transform.rotation.y), {1, 0, 0});
            model = glm::rotate(model, glm::radians(transform.rotation.z), {0, 0, 1});
            staticModelShader->setMatrix4("model", model);
            staticModelShader->setMatrix3("worldModel", glm::mat3(glm::transpose(glm::inverse(model))));
            modelComponent.model->draw(*staticModelShader);
        }

        skybox->draw(*camera, projectionMatrix, lightingData);
    }
}
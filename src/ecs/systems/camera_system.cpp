#include "camera_system.h"
#include "../components/camera_focus_component.h"
#include "../components/transform_component.h"
#include "../../input_manager.h"
#include "../../utils.h"

namespace zombies {
    const std::vector<float> ZOOM_VALUES = {20.0f, 45.0f, 60.0f, 90.0f};
    const float ZOOM_DELAY = 0.3f;
    const float DEFAULT_PITCH = -30.0f;
    const float DEFAULT_YAW = 90.0f;

    void CameraSystem::initialize(Camera *cam) {
        camera = cam;
        camera->setPitch(DEFAULT_PITCH);
        camera->setYaw(DEFAULT_YAW);

        lastMousePos = {0, 0};

        InputManager::OnMouseMove().connect(this, &CameraSystem::onMouseMove);

        InputManager::OnMouseScroll().connect([this](double x, double y) {
            cameraRadius -= (float)y;

            if (cameraRadius < 2.0f) {
                cameraRadius = 2.0f;
            }
        });
    }

    void CameraSystem::onMouseMove(double x, double y) {
        glm::vec2 mousePos = {x, y};

        float xOffset = mousePos.x - lastMousePos.x;
        float yOffset = mousePos.y - lastMousePos.y;

        float mouseSensitivity = 0.5f;
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;

        lastMousePos = mousePos;

        if (lockCamera) {
            return;
        }

        camera->changeYaw(xOffset);
        camera->changePitch(yOffset);

        camera->update();
    }

    void CameraSystem::update(entt::registry &registry, float deltaTime) {
        auto view = registry.view<CameraFocusComponent, TransformComponent>();

        if (view.size_hint() > 1) {
            throw std::runtime_error("Only one CameraFocusComponent can be attached at a time.");
        }

        processKeyboardInput(deltaTime);

        for (auto &entity: view) {
            auto &transform = registry.get<TransformComponent>(entity);
            camera->setZoom(ZOOM_VALUES.at(currentZoom));
            camera->setPosition(transform.position - camera->getFront() * cameraRadius);
            camera->update();
        }
    }

    void CameraSystem::processKeyboardInput(float deltaTime) {
        zoomChangeDelay -= deltaTime;

        if (InputManager::KeyPressed(GLFW_KEY_Z) && zoomChangeDelay <= 0) {
            // Change camera zoom
            currentZoom++;
            if (currentZoom >= ZOOM_VALUES.size()) {
                currentZoom = 0;
            }

            zoomChangeDelay = ZOOM_DELAY;
        }

        lockDelay -= deltaTime;

        if (InputManager::KeyPressed(GLFW_KEY_ENTER) && lockDelay < 0) {
            lockCamera = !lockCamera;
            lockDelay = 0.5f;
        }
    }
}
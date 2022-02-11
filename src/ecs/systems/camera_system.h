#pragma once

#include <entt/entt.hpp>
#include "../../camera.h"

namespace zombies {
    class CameraSystem {
    public:
        void initialize(Camera *cam);

        void update(entt::registry &registry, float deltaTime);

    private:
        void onMouseMove(double x, double y);

        void processKeyboardInput(float deltaTime);

        Camera *camera;

        // Position of the mouse in last frame
        glm::vec2 lastMousePos{0, 0};

        // Delays the usage of zoom
        float zoomChangeDelay = 0;
        int currentZoom = 2;

        // Distance of the spherical camera from the followed object
        float cameraRadius = 10.0f;

        bool lockCamera;
        float lockDelay;
    };
}
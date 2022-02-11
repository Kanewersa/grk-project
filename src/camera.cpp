#include "camera.h"

namespace zombies {

    Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
            : front(glm::vec3(0.0f, 0.0f, -1.0f)), zoom(ZOOM) {
        this->position = position;
        this->worldUp = worldUp;
        this->yaw = yaw;
        this->pitch = pitch;
        update();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : front(glm::vec3(0.0f, 0.0f, -1.0f)), zoom(ZOOM) {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        update();
    }

    void Camera::update() {
        glm::vec3 newFront = {
                cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                sin(glm::radians(pitch)),
                sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        };

        right = glm::normalize(glm::cross(newFront,worldUp));
        // normalize the vectors, because their length gets closer to 0 the more you look up or down,
        // which results in slower movement.
        up = glm::normalize(glm::cross(right, newFront));

        front = newFront;
    }
}
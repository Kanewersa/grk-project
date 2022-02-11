#pragma once

#include <glm/vec3.hpp>
#include <gl.h>
#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

namespace zombies {
    const float YAW = 90.0f;
    const float PITCH = 0.0f;
    const float ZOOM = 45.0f;
    const float ZNEAR = 0.1f;
    const float ZFAR = 1000.0f;

    class Camera {
    public:
        //region Getters & Setters
        glm::vec3 getPosition() {
            return position;
        }

        float getYaw() const {
            return yaw;
        }

        float getPitch() const {
            return pitch;
        }

        float getZoom() const {
            return zoom;
        }

        glm::vec3 getFront() const {
            return front;
        }

        float getZNear() const {
            return ZNEAR;
        }

        float getZFar() const {
            return ZFAR;
        }

        void setPosition(glm::vec3 newPosition) {
            position = newPosition;
        }

        void setYaw(const float newYaw) {
            yaw = fmod(newYaw, 360.0f);
        }

        void setPitch(const float newPitch) {
            pitch = fmod(newPitch, 360.0f);
        }

        void setZoom(float newZoom) {
            zoom = newZoom;
        }
        //endregion

        void changePitch(float value) {
            setPitch(pitch + value);
        }

        void changeYaw(float value) {
            setYaw(yaw + value);
        }

        explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
                        float yaw = YAW, float pitch = PITCH);

        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 getViewMatrix() {
            return glm::lookAt(position, position + front, up);
        }

        void update();

    private:
        glm::vec3 position;
        float yaw;
        float pitch;
        float zoom;
        float zNear;
        float zFar;

        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
    };
};

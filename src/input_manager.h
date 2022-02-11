#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <stdexcept>
#include <iostream>
#include "rocket.hpp"

namespace zombies {
    class InputManager {
    public:
        static void mouseCallback(GLFWwindow* window, double x, double y) {
            get().onMouseMove(x, y);
        }

        static void scrollCallback(GLFWwindow* window, double x, double y) {
            get().onMouseScroll (x, y);
        }

        static void loadWindow(GLFWwindow *win) {
            get().window = win;
            glfwSetScrollCallback(win, scrollCallback);
            glfwSetCursorPosCallback(win, mouseCallback);
        }

        static bool IsKeyDown(int key) { return glfwGetKey(get().window, key) == GLFW_KEY_DOWN; }

        static bool IsKeyUp(int key) { return glfwGetKey(get().window, key) == GLFW_KEY_UP; }

        static bool KeyPressed(int key) { return glfwGetKey(get().window, key) == GLFW_PRESS; }

        static rocket::signal<void(double x, double y)>& OnMouseMove() {
            return get().onMouseMove;
        }

        static rocket::signal<void(double x, double y)>& OnMouseScroll() {
            return get().onMouseScroll;
        }
    private:
        rocket::signal<void(double x, double y)> onMouseMove;
        rocket::signal<void(double x, double y)> onMouseScroll;

        static InputManager& get() {
            static InputManager instance;
            return instance;
        }

        GLFWwindow *window;
    };
}
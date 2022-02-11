#pragma once

// GLAD must be included before GLFW.
#include <gl.h>
#include <GLFW/glfw3.h>

namespace zombies {
    class Window {
    public:
        Window();

        ~Window();

        void show();

        void onWindowResized(GLFWwindow *win, int width, int height);

        GLFWwindow *getGLFWWindow() const { return glfwWindow; }

        int getWidth() {
            return width;
        }

        int getHeight() {
            return height;
        }

    private:
        int width;
        int height;

        GLFWwindow *glfwWindow;
    };
}
#pragma once

#include "window.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace zombies {
    class Game {
    public:
        Game();

        virtual ~Game();

        void run();

    protected:
        virtual void initialize() = 0;

        virtual void update();

        virtual void draw();

        GLFWwindow *getGLFWWindow() {
            if (window == nullptr) {
                throw std::runtime_error("Window was not initialized.");
            }

            return window->getGLFWWindow();
        };

        float getDeltaTime() const { return deltaTime; }

    protected:
        Window *window;

    private:
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
    };
}

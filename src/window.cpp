#define LIMIT_FPS 1

#include "window.h"

#include <iostream>
#include <stb_image.h>

namespace zombies {
    const int DEFAULT_WIDTH = 1280;
    const int DEFAULT_HEIGHT = 1024;

	Window::Window() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::show() {
		glfwWindow = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "LearnOpenGL", nullptr, nullptr);

		if (glfwWindow == nullptr) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window.");
		}

		glfwMakeContextCurrent(glfwWindow);

		// Flip loaded texture's on the y-axis
		stbi_set_flip_vertically_on_load(true);

		// Enable/Disable FPS limit
		glfwSwapInterval(LIMIT_FPS);

        // Set the user pointer to use it in callback
		glfwSetWindowUserPointer(glfwWindow, this);

		glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow* win, int width, int height) {
			glViewport(0, 0, width, height);
			static_cast<Window*>(glfwGetWindowUserPointer(win))->onWindowResized(win, width, height);
		});

		if (!gladLoadGL(glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD.");
		}

		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);

        this->width = DEFAULT_WIDTH;
        this->height = DEFAULT_HEIGHT;
    }

	void Window::onWindowResized(GLFWwindow* win, int width, int height) {
		this->width = width;
        this->height = height;
	}
}
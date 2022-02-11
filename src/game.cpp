#include "game.h"

namespace zombies {
	Game::Game() : window(new Window()) {

	}

	Game::~Game() {
		delete window;
	}

	void Game::run() {
		window->show();

		initialize();

		while (!glfwWindowShouldClose(window->getGLFWWindow()))
		{
            update();
			draw();

			// Swap the buffers
            glfwSwapBuffers(window->getGLFWWindow());
            // Call the events
            glfwPollEvents();
		}
	}

	void Game::update() {
	    auto currentFrame = (float)glfwGetTime();
	    deltaTime = currentFrame - lastFrame;
	    lastFrame = currentFrame;
	}

	void Game::draw() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
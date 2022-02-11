#include "world.h"

namespace zombies {
    World::World(Window *win) {
        window = win;
        camera = Camera();

        renderSystem = RenderSystem();
        uiRenderSystem = UIRenderSystem();
        movementSystem = MovementSystem();
        cameraSystem = CameraSystem();
        terrainSystem = new TerrainSystem();
        bubbleSystem = std::make_unique<BubbleSystem>();
        fishSystem = std::make_unique<FishSystem>();
    }

    World::~World() {
        delete terrainSystem;
    }

    void World::initialize() {
        renderSystem.initialize(&camera, window, &lightingData);
        uiRenderSystem.initialize(&camera, window, &lightingData);
        cameraSystem.initialize(&camera);
        terrainSystem->initialize(&camera, window, &registry, &lightingData);
        bubbleSystem->initialize(&camera, window, &lightingData);
        fishSystem->initialize(&camera, window);
    }

    void World::update(float deltaTime) {
        renderSystem.update(registry, deltaTime);
        movementSystem.update(registry, deltaTime);
        cameraSystem.update(registry, deltaTime);
        bubbleSystem->update(registry, deltaTime);
        fishSystem->update(registry, deltaTime);
    }

    void World::draw(float deltaTime) {
        terrainSystem->draw();
        renderSystem.draw(registry, deltaTime);
        bubbleSystem->draw(registry, deltaTime);
        uiRenderSystem.draw(registry, deltaTime);
    }
}
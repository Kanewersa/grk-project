#include "zombies.h"
#include "ecs/components/transform_component.h"
#include "ecs/components/player_component.h"
#include "ecs/components/animated_model_component.h"
#include "input_manager.h"
#include "ecs/components/movement_component.h"
#include "ecs/components/camera_focus_component.h"
#include "engine/animations/model.h"
#include "engine/model_manager.h"

namespace zombies {
    ZombieGame::ZombieGame() {
        world = new World(window);
    }

    ZombieGame::~ZombieGame() {
        delete world;
    }

    void ZombieGame::initialize() {
        InputManager::loadWindow(getGLFWWindow());

        world->initialize();

        auto &registry = world->getRegistry();

        // Create player
        auto playerEntity = registry.create();
        registry.emplace<TransformComponent>(playerEntity, glm::vec3(0, 20.0f, 0));

        Model *model = &ModelManager::GetModel(ModelType::Shark);
        Animation animation = Animation("models/shark/shark.dae", model);
        AnimatedModelComponent modelComponent = {*model, animation};

        registry.emplace<AnimatedModelComponent>(playerEntity, modelComponent);
        registry.emplace<MovementComponent>(playerEntity, 3.0f);
        registry.emplace<PlayerComponent>(playerEntity);

        // Make camera follow player
        registry.emplace<CameraFocusComponent>(playerEntity);
    }

    void ZombieGame::draw() {
        Game::draw();

        world->draw(getDeltaTime());
    }

    void ZombieGame::update() {
        Game::update();

        world->update(getDeltaTime());

        if (glfwGetKey(getGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(getGLFWWindow(), true);
    }
}

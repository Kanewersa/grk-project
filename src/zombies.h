#pragma once

#include "game.h"
#include "engine/shader.h"
#include "camera.h"
#include "ecs/world.h"

namespace zombies {
    class ZombieGame : public Game {
    public:
        ZombieGame();

        ~ZombieGame() override;

        void initialize() override;

        void draw() override;

        void update() override;

    private:
        World *world;
    };
}

#pragma once

#include "systems/render_system.h"
#include "systems/movement_system.h"
#include "systems/camera_system.h"
#include "systems/ui_render_system.h"
#include "systems/terrain_system.h"
#include "systems/bubble_system.h"
#include "systems/fish_system.h"

namespace zombies {
    class World {
    public:
        explicit World(Window *window);

        ~World();

        void initialize();

        void update(float deltaTime);

        void draw(float deltaTime);

        entt::entity createEntity() { return registry.create(); }

        entt::registry &getRegistry() { return registry; }

    private:
        entt::registry registry;

        Camera camera;
        Window *window;

        // Systems
        RenderSystem renderSystem;
        UIRenderSystem uiRenderSystem;
        MovementSystem movementSystem;
        CameraSystem cameraSystem;
        std::unique_ptr<BubbleSystem> bubbleSystem;
        std::unique_ptr<FishSystem> fishSystem;
        TerrainSystem *terrainSystem;

        // Lighting
        LightingData lightingData;
    };
}
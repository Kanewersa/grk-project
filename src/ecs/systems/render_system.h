#pragma once

#include <entt/entt.hpp>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include "../../engine/shader.h"
#include "../../camera.h"
#include "../../window.h"
#include "../../engine/cubemap.h"
#include "../../engine/skybox.h"
#include "../../engine/water/water_frame_buffers.h"
#include "../../engine/texture.h"
#include "../../engine/sprite_batch.h"
#include "../../engine/animations/model.h"
#include "../../engine/animations/animation.h"
#include "../../engine/animations/animator.h"
#include "../../engine/lighting_data.h"

namespace zombies {
    class RenderSystem {
    public:
        ~RenderSystem();

        void initialize(Camera *cam, Window *window, LightingData *lightingData);

        void update(entt::registry &registry, float deltaTime);

        void draw(entt::registry &registry, float deltaTime);

    private:
        Camera *camera;
        Window *window;
        Shader *staticModelShader;
        Shader *animatedModelShader;
        WaterFrameBuffers *waterFrameBuffers;

        Animator *animator;

        Skybox *skybox;
        LightingData *lightingData;
    };
}
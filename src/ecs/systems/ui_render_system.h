#include "entt/entt.hpp"
#include "../../window.h"
#include "imgui.h"
#include "../../camera.h"
#include "../../engine/lighting_data.h"

namespace zombies {
    class UIRenderSystem {
    public:
        void initialize(Camera* cam, Window *win, LightingData* lightingData);

        void update();

        void draw(entt::registry &registry, float deltaTime);

    private:
        Window* window;
        Camera* camera;
        LightingData* lightingData;
    };
}
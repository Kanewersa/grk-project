#include "ui_render_system.h"
#include "imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace zombies {
    void UIRenderSystem::initialize(Camera* cam, Window* win, LightingData* lighting) {
        camera = cam;
        window = win;
        lightingData = lighting;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window->getGLFWWindow(), true);
        const char *glsl_version = "#version 400";
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void UIRenderSystem::draw(entt::registry &registry, float deltaTime) {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Camera window
        {
            ImGui::Begin("Camera info");

            ImGui::Text("Position: %f, %f, %f", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
            ImGui::Text("Yaw: %f", camera->getYaw());
            ImGui::Text("Pitch: %f", camera->getPitch());

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Press Space to (un)lock camera.");
            ImGui::End();
        }

        // Lighting window
        {
            ImGui::Begin("Graphic settings");

            ImGui::Text("Light direction");
            ImGui::SliderFloat("x", &lightingData->direction.x, -1.0f, 1.0f);
            ImGui::SliderFloat("y", &lightingData->direction.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &lightingData->direction.z, -1.0f, 1.0f);
            if (ImGui::Button("Reset direction")) {
                lightingData->direction = {0, 0, 0};
            }

            ImGui::Text("Light color");
            ImGui::SliderFloat("r", &lightingData->color.x, 0.0f, 1.0f);
            ImGui::SliderFloat("g", &lightingData->color.y, 0.0f, 1.0f);
            ImGui::SliderFloat("b", &lightingData->color.z, 0.0f, 1.0f);

            ImGui::Text("Fog settings");
            ImGui::Text("Color");
            ImGui::SliderFloat("cr", &lightingData->fogColor.x, 0.0f, 1.0f);
            ImGui::SliderFloat("cg", &lightingData->fogColor.y, 0.0f, 1.0f);
            ImGui::SliderFloat("cb", &lightingData->fogColor.z, 0.0f, 1.0f);

            ImGui::Text("Density & Gradient");
            ImGui::SliderFloat("Density", &lightingData->fogDensity, 0.0f, 0.1f);
            ImGui::SliderFloat("Gradient", &lightingData->fogGradient, 0.0f, 5.0f);

            ImGui::Text("Render distance");
            ImGui::SliderFloat("Object distance", &lightingData->objectRenderDistance, 0.0f, 500.0f);
            ImGui::SliderInt("Terrain distance", &lightingData->terrainRenderDistance, 0, 10);

            ImGui::Checkbox("Flat terrain", &lightingData->flatTerrain);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

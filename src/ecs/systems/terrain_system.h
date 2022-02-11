#pragma once

#include <string>
#include <utility>
#include <unordered_map>
#include <random>
#include "../../engine/shader.h"
#include "noise.h"
#include "../../camera.h"
#include "../../window.h"
#include "../../engine/animations/model.h"
#include "../../engine/shader_manager.h"
#include "entt/entt.hpp"
#include "../components/transform_component.h"
#include "../components/model_component.h"
#include "../components/movement_component.h"
#include "../components/fish_component.h"
#include "../components/plant_component.h"
#include "../../engine/model_manager.h"
#include "../../engine/terrain/chunk.h"
#include "../../engine/terrain/chunk_generator.h"
#include "../../engine/lighting_data.h"

namespace zombies {
    class TerrainSystem {
    public:
        TerrainSystem() = default;

        ~TerrainSystem() {
            chunkGenerator->Finish();
            thread->join();
            delete chunkGenerator;
            delete thread;
            for (auto &chunk: chunks) {
                glDeleteVertexArrays(1, &chunk.second);
            }
            // TODO VBOs and EBOs aren't being deleted
        }

        void initialize(Camera *cam, Window *win, entt::registry *reg, LightingData *lightingData);

        void draw();

        void render(glm::mat4 &view, glm::mat4 &projection);

    private:
        void generateChunkData(std::string const &key);

        void generateBuffers(std::string const &key);

        ChunkGenerator *chunkGenerator;
        std::thread *thread;
        // Class variables
        Camera *camera;
        Window *window;
        Shader *terrainShader;
        entt::registry *registry;
        LightingData *lighting;
        std::unordered_map<std::string, GLuint> chunks;
        std::unordered_map<std::string, ChunkData> chunksData;
        std::unordered_map<std::string, std::vector<PlantData>> plantsData;

        const int INDICES_COUNT = Chunk::WIDTH * Chunk::HEIGHT * 6;  // Indices count per chunk
    };
}

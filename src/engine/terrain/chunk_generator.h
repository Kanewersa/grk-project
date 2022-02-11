#pragma once

#include <chrono>
#include <thread>
#include <unordered_map>
#include "../../camera.h"
#include "chunk.h"
#include "../../ecs/components/model_component.h"
#include "../model_manager.h"
#include "../../ecs/systems/noise.h"
#include "entt/entt.hpp"
#include "../../ecs/components/transform_component.h"
#include "../../engine/lighting_data.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

namespace zombies {
    struct ChunkData {
        std::vector<int> indices;
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> colors;
        glm::vec2 chunkCoords;
    };

    struct PlantData {
        glm::vec3 position;
        ModelType plantType;

        PlantData(glm::vec3 pos, ModelType modelType) {
            position = pos;
            plantType = modelType;
        }
    };

    class ChunkGenerator {
    public:
        struct TerrainColor {
            float height;
            glm::vec3 color{};

            TerrainColor(float height, glm::vec3 color) {
                this->height = height;
                this->color = color;
            };
        };

        ChunkGenerator(std::unordered_map<std::string, GLuint> &chunksMap,
                       std::unordered_map<std::string, ChunkData> &chunksDataMap,
                       std::unordered_map<std::string, std::vector<PlantData>> &plantsDataMap, LightingData *lightingData) : chunks(chunksMap),
                                                                                                 chunksData(
                                                                                                         chunksDataMap),
                                                                                                 plantsData(
                                                                                                         plantsDataMap) {
            this->chunks = chunksMap;
            this->chunksData = chunksDataMap;
            this->plantsData = plantsDataMap;
            this->lighting = lightingData;
            exit = false;
        }

        void generateChunks(Camera *cam, entt::registry *reg);

        void Finish() {
            exit = true;
        }

    private:
        void generateMapChunk(int chunkX, int chunkY, std::string const &key);

        static std::vector<int> generateChunkIndices();

        static std::vector<float> generateNoiseMap(int chunkX, int chunkY);

        static std::vector<float> generateVertices(const std::vector<float> &noise_map);

        static std::vector<float> generateNormals(const std::vector<int> &indices, const std::vector<float> &vertices);

        std::vector<float>
        generateBiome(const std::vector<float> &vertices, int chunkX, int chunkY, std::string const &key);

        static glm::vec3 GetColor(int r, int g, int b) {
            return {r / 255.0, g / 255.0, b / 255.0};
        }

        // Terrain params
        constexpr static const float MESH_HEIGHT = 24;  // Vertical scaling
        constexpr static const float NOISE_SCALE = 64;  // Horizontal scale
        constexpr static const float PERSISTENCE = 0.5;
        constexpr static const float LACUNARITY = 2;
        constexpr static const float GROUND_HEIGHT = 0.1;
        static const int OCTAVES = 7;

        entt::registry *registry;
        std::unordered_map<std::string, GLuint> &chunks;
        std::unordered_map<std::string, ChunkData> &chunksData;
        std::unordered_map<std::string, std::vector<PlantData>> &plantsData;
        LightingData *lighting;

        std::vector<TerrainColor> biomeColors;
        bool exit;
        Camera *camera;
    };
}

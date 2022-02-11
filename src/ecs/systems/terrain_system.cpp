#include "terrain_system.h"

namespace zombies {

    void TerrainSystem::initialize(Camera *cam, Window *win, entt::registry *reg, LightingData *lightingData) {
        this->camera = cam;
        this->window = win;
        this->registry = reg;
        this->lighting = lightingData;

        // Load terrain shader
        terrainShader = &ShaderManager::GetShader(ShaderType::Terrain);

        terrainShader->use();

        // Lighting intensities and direction
        // TODO: Move terrain lighting settings to lighting data!
        terrainShader->setVector3f("light.diffuse", 0.3, 0.3, 0.3);
        terrainShader->setVector3f("light.specular", 1.0, 1.0, 1.0);

        chunkGenerator = new ChunkGenerator(chunks, chunksData, plantsData, lightingData);
        thread = new std::thread(&ChunkGenerator::generateChunks, chunkGenerator, camera, registry);
    }

    void TerrainSystem::draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        terrainShader->use();
        // Set terrain coloring mode
        terrainShader->setBool("isFlat", lighting->flatTerrain);
        terrainShader->setVector3f("light.color", lighting->color);
        terrainShader->setVector3f("light.direction", lighting->direction.x, lighting->direction.y, lighting->direction.z);
        terrainShader->setVector3f("fogColor", lighting->fogColor.x, lighting->fogColor.y, lighting->fogColor.z);
        terrainShader->setFloat("density", lighting->fogDensity);
        terrainShader->setFloat("gradient", lighting->fogGradient);

        float aspectRatio = (float) window->getWidth() / (float) window->getHeight();
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera->getZoom()), aspectRatio,
                                                      camera->getZNear(), camera->getZFar());
        glm::mat4 viewMatrix = camera->getViewMatrix();
        terrainShader->setMatrix4("projection", projectionMatrix);
        terrainShader->setMatrix4("view", viewMatrix);
        terrainShader->setVector3f("viewPos", camera->getPosition());
        render(viewMatrix, projectionMatrix);
    }

    void TerrainSystem::render(glm::mat4 &view, glm::mat4 &projection) {
        int currentChunkX = (int) camera->getPosition().x / Chunk::WIDTH;
        int currentChunkY = (int) camera->getPosition().z / Chunk::HEIGHT;
        glm::mat4 model;

        int renderDistance = lighting->terrainRenderDistance;

        // Render visible chunks
        for (int y = currentChunkY - renderDistance; y < currentChunkY + renderDistance; ++y) {
            for (int x = currentChunkX - renderDistance; x < currentChunkY + renderDistance; ++x) {
                std::string key = Chunk::GetPositionKey(x, y);

                // Render only loaded chunks
                if (chunks.contains(key)) {
                    if (chunks[key] == 0) {
                        generateChunkData(key);
                        continue;
                    }
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(-Chunk::WIDTH / 2.0 + (Chunk::WIDTH - 1) * x, 0.0,
                                                            -Chunk::HEIGHT / 2.0 + (Chunk::HEIGHT - 1) * y));
                    terrainShader->setMatrix4("model", model);

                    // Draw chunk
                    glBindVertexArray(chunks[Chunk::GetPositionKey(x, y)]);
                    glDrawElements(GL_TRIANGLES, INDICES_COUNT, GL_UNSIGNED_INT, 0);
                }
            }
        }
    }

    void TerrainSystem::generateChunkData(const std::string &key) {
        // Generate VAO, VBO and EBO on main thread
        generateBuffers(key);

        //  Create plant entities on main thread
        for (const auto &plantData : plantsData[key]) {
            auto entity = registry->create();
            glm::vec3 rotation = {rand() % 100, 0, 0};
            if (plantData.plantType == ModelType::BigAlgae) {
                rotation += glm::vec3(0, 0, -90.0f);
            }

            float scaleFactor = std::max(Utils::RandomFloat() + 0.5f, 1.0f);
            auto scale = glm::vec3(scaleFactor);
            registry->emplace<TransformComponent>(entity, plantData.position + glm::vec3{0, 0.75f, 0}, rotation, scale);
            registry->emplace<ModelComponent>(entity, &ModelManager::GetModel(plantData.plantType));
            registry->emplace<PlantComponent>(entity, plantData.plantType);
        }

        // Spawn some fish per chunk
        for (int i = 0; i < rand() % 70 + 30; ++i) {
            auto entity = registry->create();
            TransformComponent transformComponent;
            glm::vec2 coords = chunksData[key].chunkCoords;
            glm::vec3 randomPos = {rand() % Chunk::WIDTH, rand() % 10 + 5, rand() % Chunk::HEIGHT};
            transformComponent.position = {coords.x * Chunk::WIDTH + randomPos.x, randomPos.y, coords.y * Chunk::HEIGHT + randomPos.z};
            float scale = Utils::RandomFloat()/2 + 0.2f;
            // (0, 0.5) + 0.2
            transformComponent.scale = glm::vec3(scale);
            registry->emplace<TransformComponent>(entity, transformComponent);
            float modelValue = Utils::RandomFloat();
            ModelType fishType;
            if (modelValue <= 0.33f) {
                fishType = ModelType::Fish;
            } else if (modelValue <= 0.66f) {
                fishType = ModelType::CoralFish;
            } else {
                fishType = ModelType::SpecialFish;
            }
            registry->emplace<ModelComponent>(entity, &ModelManager::GetModel(fishType));
            registry->emplace<MovementComponent>(entity, Utils::RandomFloat() * 2 + 0.7f);
            registry->emplace<FishComponent>(entity);
        }
    }

    void TerrainSystem::generateBuffers(const std::string &key) {
        GLuint VAO;
        GLuint VBO[3];
        GLuint EBO;

        ChunkData *data = &chunksData[key];

        glGenBuffers(3, VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, data->vertices.size() * sizeof(float), &data->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indices.size() * sizeof(int), &data->indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, data->normals.size() * sizeof(float), &data->normals[0], GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, data->colors.size() * sizeof(float), &data->colors[0], GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(2);

        // Save VAO in chunks map
        chunks[key] = VAO;
    }
}

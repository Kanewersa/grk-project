#include "chunk_generator.h"

namespace zombies {

    void ChunkGenerator::generateChunks(Camera *cam, entt::registry *reg) {
        this->camera = cam;
        this->registry = reg;

        // Create biome colors
        biomeColors.emplace_back(GROUND_HEIGHT * 0.5, GetColor(75, 60, 55)); // Dirt 1
        biomeColors.emplace_back(GROUND_HEIGHT, GetColor(75, 60, 55));       // Dirt 1
        biomeColors.emplace_back(0.15, GetColor(210, 215, 130));             // Sand 1
        biomeColors.emplace_back(0.30, GetColor(200, 205, 120));             // Sand 2
        biomeColors.emplace_back(0.40, GetColor(220, 225, 140));             // Sand 3
        biomeColors.emplace_back(0.80, GetColor(75, 60, 55));                // Dirt 1
        biomeColors.emplace_back(0.50, GetColor(90, 65, 60));                // Dirt 2
        biomeColors.emplace_back(1.00, GetColor(100, 75, 70));               // Dirt 3

        while (true) {
            if (exit) {
                break;
            }

            // Keep generating new chunks based on camera pos
            int currentChunkX = (int) cam->getPosition().x / Chunk::WIDTH;
            int currentChunkY = (int) cam->getPosition().z / Chunk::HEIGHT;

            glm::mat4 model;

            int renderDistance = lighting->terrainRenderDistance;

            for (int y = currentChunkY - renderDistance; y < currentChunkY + renderDistance; ++y) {
                for (int x = currentChunkX - renderDistance; x < currentChunkY + renderDistance; ++x) {
                    std::string key = Chunk::GetPositionKey(x, y);
                    if (!chunks.contains(key)) {
                        generateMapChunk(x, y, key);
                    }
                }
            }

            sleep_for(10ms);
        }
    }

    void ChunkGenerator::generateMapChunk(int chunkX, int chunkY, const std::string &key) {
        std::vector<float> noiseMap = generateNoiseMap(chunkX, chunkY);

        chunksData[key] = ChunkData();
        ChunkData *data = &chunksData[key];
        data->indices = generateChunkIndices();
        data->vertices = generateVertices(noiseMap);
        data->normals = generateNormals(data->indices, data->vertices);
        data->colors = generateBiome(data->vertices, chunkX, chunkY, key);
        data->chunkCoords = {chunkX, chunkY};

        chunks[key] = 0;
    }

    std::vector<int> ChunkGenerator::generateChunkIndices() {
        std::vector<int> indices;

        for (int y = 0; y < Chunk::HEIGHT; y++)
            for (int x = 0; x < Chunk::WIDTH; x++) {
                int pos = x + y * Chunk::WIDTH;

                if (x == Chunk::WIDTH - 1 || y == Chunk::HEIGHT - 1) {
                    // Don't create indices for right or top edge
                    continue;
                } else {
                    // Top left triangle
                    indices.push_back(pos + Chunk::WIDTH);
                    indices.push_back(pos);
                    indices.push_back(pos + Chunk::WIDTH + 1);
                    // Bottom right triangle
                    indices.push_back(pos + 1);
                    indices.push_back(pos + 1 + Chunk::WIDTH);
                    indices.push_back(pos);
                }
            }

        return indices;
    }

    std::vector<float> ChunkGenerator::generateNoiseMap(int chunkX, int chunkY) {
        std::vector<float> noiseValues;
        float amplitude = 1;
        float frequency;
        float maxHeight = 0;

        std::vector<int> seed = Noise::get_permutation_vector();

        for (int i = 0; i < OCTAVES; i++) {
            maxHeight += amplitude;
            amplitude *= PERSISTENCE;
        }

        for (int y = 0; y < Chunk::HEIGHT; y++) {
            for (int x = 0; x < Chunk::WIDTH; x++) {
                amplitude = 1;
                frequency = 1;
                float noiseHeight = 0;
                for (int i = 0; i < OCTAVES; i++) {
                    float xSample = float(x + chunkX * (Chunk::WIDTH - 1)) / NOISE_SCALE * frequency;
                    float ySample = float(y + chunkY * (Chunk::HEIGHT - 1)) / NOISE_SCALE * frequency;

                    noiseHeight += (float) Noise::perlin_noise(xSample, ySample, seed) * amplitude;

                    amplitude *= PERSISTENCE; // Changes the amplitude of octaves
                    frequency *= LACUNARITY; // Changes the frequency of octaves
                }

                noiseValues.push_back((noiseHeight + 1) / maxHeight);
            }
        }

        return noiseValues;
    }

    std::vector<float> ChunkGenerator::generateVertices(const std::vector<float> &noise_map) {
        std::vector<float> vertices;
        vertices.reserve(Chunk::WIDTH * Chunk::HEIGHT * 3);

        for (int y = 0; y < Chunk::HEIGHT; y++) {
            for (int x = 0; x < Chunk::WIDTH; x++) {
                vertices.push_back((float) x);
                // Apply cubic easing to the noise so that it becomes smooth
                auto easedNoise = (float) std::pow(noise_map[x + y * Chunk::WIDTH] * 1.1, 3);

                // Scale noise to match height of the mesh and prevent vertex height from being too low (below ground height)
                vertices.push_back((float) std::fmax(easedNoise * MESH_HEIGHT, GROUND_HEIGHT * 0.5 * MESH_HEIGHT));
                vertices.push_back((float) y);
            }
        }

        return vertices;
    }

    std::vector<float>
    ChunkGenerator::generateNormals(const std::vector<int> &indices, const std::vector<float> &vertices) {
        int vertexIndex;
        glm::vec3 normal;
        std::vector<float> normals;
        std::vector<glm::vec3> vs;

        // Get the vertices of each triangle in the mesh
        // For each group of indices
        for (int i = 0; i < indices.size(); i += 3) {

            // Get the vertex for every index
            for (int j = 0; j < 3; j++) {
                vertexIndex = indices[i + j] * 3;
                vs.emplace_back(vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]);
            }

            // Get vectors of the two edges of the triangle
            // V = P2 - P1
            // W = P3 - P1
            glm::vec3 V = vs[i + 2] - vs[i];
            glm::vec3 W = vs[i + 1] - vs[i];

            // Calculate normal
            normal = glm::normalize(glm::cross(V, W));
            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);
        }

        return normals;
    }

    std::vector<float>
    ChunkGenerator::generateBiome(const std::vector<float> &vertices, int chunkX, int chunkY, const std::string &key) {
        std::vector<float> colors;
        glm::vec3 color = GetColor(255, 255, 255);

        ModelType plantType;
        plantsData[key] = std::vector<PlantData>();

        for (int i = 1; i < vertices.size(); i += 3) {
            for (int j = 0; j < biomeColors.size(); j++) {
                if (vertices[i] <= biomeColors[j].height * MESH_HEIGHT) {
                    color = biomeColors[j].color;

                    // Spawn plants only on certain biomes
                    if (j <= 4) {
                        // Create plants with a certain chance
                        if (rand() % 1000 < 25) {
                            float value = rand() % 100;
                            if (value <= 33) {
                                float colorValue = Utils::RandomFloat();

                                if (colorValue <= 0.2f) {
                                    plantType = ModelType::SmallAlgae;
                                } else if (colorValue <= 0.4f) {
                                    plantType = ModelType::SmallRedAlgae;
                                } else if (colorValue <= 0.6f) {
                                    plantType = ModelType::SmallBlueAlgae;
                                } else if (colorValue <= 0.8f) {
                                    plantType = ModelType::SmallPurpleAlgae;
                                } else {
                                    plantType = ModelType::SmallYellowAlgae;
                                }

                            } else if (value <= 66) {
                                plantType = ModelType::BigAlgae;
                            } else {
                                float colorValue = Utils::RandomFloat();

                                if (colorValue <= 0.5f) {
                                    plantType = ModelType::MediumAlgae;
                                } else if (colorValue <= 0.6f) {
                                    plantType = ModelType::MediumRedAlgae;
                                } else if (colorValue <= 0.75f) {
                                    plantType = ModelType::MediumBlueAlgae;
                                } else if (colorValue <= 0.85f) {
                                    plantType = ModelType::MediumPurpleAlgae;
                                } else {
                                    plantType = ModelType::MediumYellowAlgae;
                                }
                            }

                            glm::vec3 pos = {
                                    -Chunk::WIDTH / 2.0 + (Chunk::WIDTH - 1) * chunkX + vertices[i - 1],
                                    vertices[i],
                                    -Chunk::HEIGHT / 2.0 + (Chunk::HEIGHT - 1) * chunkY + vertices[i + 1]
                            };

                            plantsData[key].emplace_back(pos, plantType);
                        }
                    }
                    break;
                }
            }
            colors.push_back(color.r);
            colors.push_back(color.g);
            colors.push_back(color.b);
        }
        return colors;
    }
}

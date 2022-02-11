#pragma once

#include <vector>
#include "../shader.h"

namespace zombies {
#define MAX_BONE_INFLUENCE 4

    struct TextureData {
        unsigned int id;
        std::string type;
        std::string path;
    };

    struct VertexData {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        // Indexes of bones, that influence this vertex data.
        int boneIds[MAX_BONE_INFLUENCE];

        // Weights from every bone.
        float weights[MAX_BONE_INFLUENCE];
    };

    class Mesh {
    public:
        Mesh(std::vector<VertexData> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures);

        void draw(const Shader &shader);

    protected:
        void setupMesh();

        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;
        std::vector<TextureData> textures;

        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;
    };
}

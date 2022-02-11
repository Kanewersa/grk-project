#pragma once

#include <gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "bone.h"

namespace zombies {
    class Model {
    public:
        // Store all the textures to prevent loading them more than once
        std::vector<TextureData> loadedTextures;
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

        explicit Model(std::string const &path, bool gamma = false);

        void draw(Shader &shader);

        auto &getOffsetMatMap() { return matrixOffsets; }

        int &getBoneCount() { return bonesCount; }


    private:
        std::map<std::string, BoneInfo> matrixOffsets;
        int bonesCount = 0;

        void loadModel(std::string const &path);

        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        void extractBoneWeightForVertices(std::vector<VertexData> &vertices, aiMesh *mesh, const aiScene *scene);

        std::vector<TextureData>
        loadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string &typeName);

        static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

        static void SetDefaultBoneData(VertexData &vertex);

        static void SetBoneData(VertexData &vertex, int boneID, float weight);
    };
}

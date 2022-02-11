#include "model.h"
#include "../../print.h"

namespace zombies {
    Model::Model(const std::string &path, bool gamma) : gammaCorrection(gamma) {
        loadModel(path);
    }

    void Model::draw(Shader &shader) {
        for (auto &mesh: meshes) {
            mesh.draw(shader);
        }
    }

    void Model::loadModel(std::string const &path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                       aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }

        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        // Process child nodes after processing current node
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<VertexData> vertices;
        vertices.reserve(mesh->mNumVertices);
        std::vector<unsigned int> indices;
        std::vector<TextureData> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            VertexData vertex{};
            SetDefaultBoneData(vertex);
            vertex.position = Utils::GetGlmVec(mesh->mVertices[i]);
            vertex.normal = Utils::GetGlmVec(mesh->mNormals[i]);

            if (mesh->mTextureCoords[0]) {
                vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            } else {
                vertex.texCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<TextureData> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<TextureData> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR,
                                                                     "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector<TextureData> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        std::vector<TextureData> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        extractBoneWeightForVertices(vertices, mesh, scene);

        return {vertices, indices, textures};
    }

    std::vector<TextureData>
    Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string &typeName) {
        std::vector<TextureData> textures;

        for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
            aiString texturePath;
            material->GetTexture(type, i, &texturePath);

            // Skip loading the texture if it is already loaded
            bool textureLoaded = false;
            for (auto &loadedTexture: loadedTextures) {
                // Compare texture names
                if (std::strcmp(loadedTexture.path.data(), texturePath.C_Str()) == 0) {
                    textures.push_back(loadedTexture);
                    textureLoaded = true;
                    break;
                }
            }

            if (!textureLoaded) {
                TextureData texture;
                texture.id = TextureFromFile(texturePath.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = texturePath.C_Str();
                textures.push_back(texture);
                loadedTextures.push_back(texture);
            }
        }

        return textures;
    }

    void Model::extractBoneWeightForVertices(std::vector<VertexData> &vertices, aiMesh *mesh, const aiScene *scene) {
        auto &boneInfoMap = matrixOffsets;
        int &boneCount = bonesCount;

        for (unsigned int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
            int boneID = -1;
            std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
            if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
                BoneInfo newBoneInfo{};
                newBoneInfo.id = boneCount;
                newBoneInfo.offset = Utils::GetGlmMatrix(mesh->mBones[boneIndex]->mOffsetMatrix);
                boneInfoMap[boneName] = newBoneInfo;
                boneID = boneCount;
                boneCount++;
            } else {
                boneID = boneInfoMap[boneName].id;
            }
            assert(boneID != -1);
            auto weights = mesh->mBones[boneIndex]->mWeights;
            unsigned int numWeights = mesh->mBones[boneIndex]->mNumWeights;

            for (unsigned int weightIndex = 0; weightIndex < numWeights; ++weightIndex) {
                unsigned int vertexId = weights[weightIndex].mVertexId;
                float weight = weights[weightIndex].mWeight;
                assert(vertexId <= vertices.size());
                SetBoneData(vertices[vertexId], boneID, weight);
            }
        }
    }

    void Model::SetDefaultBoneData(VertexData &vertex) {
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
            vertex.boneIds[i] = -1;
            vertex.weights[i] = 0.0f;
        }
    }

    void Model::SetBoneData(VertexData &vertex, int boneID, float weight) {
        for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
            if (vertex.boneIds[i] < 0) {
                vertex.weights[i] = weight;
                vertex.boneIds[i] = boneID;
                return;
            }
        }
    }

    unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma) {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        stbi_set_flip_vertically_on_load(true);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        } else {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
}

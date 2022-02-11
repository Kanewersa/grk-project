#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "bone.h"
#include <functional>
#include "assimp/Importer.hpp"
#include "model.h"

namespace zombies {
    struct AssimpNodeData {
        glm::mat4 transformation;
        std::string name;
        unsigned int childrenCount;
        std::vector<AssimpNodeData> children;
    };

    class Animation {
    public:
        Animation() = default;

        Animation(const std::string &animationPath, Model *model);

        ~Animation() = default;

        Bone *findBone(const std::string &name);

        inline float getTicksPerSecond() const { return ticksPerSecond; }

        inline float getDuration() const { return duration; }

        inline const AssimpNodeData &getRootNode() { return rootNode; }

        inline const std::map<std::string, BoneInfo> &getBoneIDMap() {
            return boneInfoMap;
        }

    private:
        void setupBones(const aiAnimation *animation, Model &model);

        void readHierarchyData(AssimpNodeData &dest, const aiNode *src);

        float duration;
        float ticksPerSecond;
        std::vector<Bone> bones;
        AssimpNodeData rootNode;
        std::map<std::string, BoneInfo> boneInfoMap;
    };
}

#include "animation.h"

namespace zombies {

    Animation::Animation(const std::string &animationPath, Model *model) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
        assert(scene && scene->mRootNode);
        auto animation = scene->mAnimations[0];
        duration = (float) animation->mDuration;
        ticksPerSecond = (float) animation->mTicksPerSecond;
        readHierarchyData(rootNode, scene->mRootNode);
        setupBones(animation, *model);
    }

    Bone *Animation::findBone(const std::string &name) {
        auto iter = std::find_if(bones.begin(), bones.end(),
                                 [&](const Bone &Bone) {
                                     return Bone.getName() == name;
                                 }
        );

        if (iter == bones.end()) {
            return nullptr;
        } else {
            return &(*iter);
        }
    }

    void Animation::setupBones(const aiAnimation *animation, Model &model) {
        unsigned int size = animation->mNumChannels;

        auto &boneMap = model.getOffsetMatMap();
        int &boneCount = model.getBoneCount();

        for (unsigned int i = 0; i < size; i++) {
            auto channel = animation->mChannels[i];
            std::string boneName = channel->mNodeName.data;

            if (boneMap.find(boneName) == boneMap.end()) {
                boneMap[boneName].id = boneCount;
                boneCount++;
            }
            bones.emplace_back(channel->mNodeName.data,
                               boneMap[channel->mNodeName.data].id, channel);
        }

        boneInfoMap = boneMap;
    }

    void Animation::readHierarchyData(AssimpNodeData &dest, const aiNode *src) {
        assert(src);

        dest.name = src->mName.data;
        dest.transformation = Utils::GetGlmMatrix(src->mTransformation);
        dest.childrenCount = src->mNumChildren;

        for (unsigned int i = 0; i < src->mNumChildren; i++) {
            AssimpNodeData newData;
            readHierarchyData(newData, src->mChildren[i]);
            dest.children.push_back(newData);
        }
    }
}

#include "animator.h"
#include "../../print.h"

namespace zombies {

    Animator::Animator(Animation *current) {
        currentAnimation = current;
        currentTime = 0.0;
        playSpeed = 1.0f;
        transforms.reserve(100);

        for (int i = 0; i < 100; i++) {
            transforms.emplace_back(1.0f);
        }
    }

    void Animator::update(float deltaTime) {
        if (currentAnimation) {
            currentTime += currentAnimation->getTicksPerSecond() * deltaTime * playSpeed;
            currentTime = fmod(currentTime, currentAnimation->getDuration());
            calculateBoneTransform(&currentAnimation->getRootNode(), glm::mat4(1.0f));
        }
    }

    void Animator::playAnimation(Animation *pAnimation) {
        currentAnimation = pAnimation;
        currentTime = 0.0f;
        initializeTransforms(&currentAnimation->getRootNode(), currentAnimation->getRootNode().transformation);
    }

    void Animator::initializeTransforms(const AssimpNodeData *node, glm::mat4 parentTransform) {
        std::string nodeName = node->name;
        glm::mat4 nodeTransform = node->transformation;

        glm::mat4 globalTransformation = parentTransform * nodeTransform;
        auto boneInfoMap = currentAnimation->getBoneIDMap();
        if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
            int index = boneInfoMap[nodeName].id;
            glm::mat4 offset = boneInfoMap[nodeName].offset;
            transforms[index] = globalTransformation * offset;
        }

        for (unsigned int i = 0; i < node->childrenCount; i++) {
            initializeTransforms(&node->children[i], globalTransformation);
        }
    }

    void Animator::calculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform) {
        std::string nodeName = node->name;
        glm::mat4 nodeTransform = node->transformation;

        Bone *Bone = currentAnimation->findBone(nodeName);

        if (Bone) {
            Bone->update(currentTime);
            nodeTransform = Bone->getLocalTransform();
        }

        glm::mat4 globalTransformation = parentTransform * nodeTransform;

        auto boneInfoMap = currentAnimation->getBoneIDMap();

        if (boneInfoMap.find(nodeName) != boneInfoMap.end()) {
            int index = boneInfoMap[nodeName].id;
            glm::mat4 offset = boneInfoMap[nodeName].offset;
            transforms[index] = globalTransformation * offset;
        }

        for (unsigned int i = 0; i < node->childrenCount; i++) {
            calculateBoneTransform(&node->children[i], globalTransformation);
        }
    }
}

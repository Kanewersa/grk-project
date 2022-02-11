#include "bone.h"

namespace zombies {
    Bone::Bone(const std::string &name, int id, const aiNodeAnim *nodeAnim) : name(name), id(id), transform(1.0f) {
        positionsCount = nodeAnim->mNumPositionKeys;
        for (unsigned int positionIndex = 0; positionIndex < positionsCount; ++positionIndex) {
            KeyFramePosition data{
                    Utils::GetGlmVec(nodeAnim->mPositionKeys[positionIndex].mValue),
                    (float) nodeAnim->mPositionKeys[positionIndex].mTime
            };

            positions.push_back(data);
        }

        rotationsCount = nodeAnim->mNumRotationKeys;
        for (unsigned int rotationIndex = 0; rotationIndex < rotationsCount; ++rotationIndex) {
            KeyFrameRotation data{
                    Utils::GetGlmQuat(nodeAnim->mRotationKeys[rotationIndex].mValue),
                    (float) nodeAnim->mRotationKeys[rotationIndex].mTime
            };

            rotations.push_back(data);
        }

        scalesCount = nodeAnim->mNumScalingKeys;
        for (unsigned int keyIndex = 0; keyIndex < scalesCount; ++keyIndex) {
            KeyFrameScale data{
                    Utils::GetGlmVec(nodeAnim->mScalingKeys[keyIndex].mValue),
                    (float) nodeAnim->mScalingKeys[keyIndex].mTime
            };

            scales.push_back(data);
        }
    }

    float Bone::getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) {
        float scaleFactor = 0.0f;
        float midWayLength = animationTime - lastTimeStamp;
        float framesDiff = nextTimeStamp - lastTimeStamp;
        scaleFactor = midWayLength / framesDiff;
        return scaleFactor;
    }

    glm::mat4 Bone::interpolatePosition(float animationTime) {
        if (1 == positionsCount)
            return glm::translate(glm::mat4(1.0f), positions[0].position);

        unsigned int p0Index = getPositionIndex(animationTime);
        unsigned int p1Index = p0Index + 1;
        float scaleFactor = getScaleFactor(positions[p0Index].timeStamp,
                                           positions[p1Index].timeStamp, animationTime);
        glm::vec3 finalPosition = glm::mix(positions[p0Index].position, positions[p1Index].position,
                                           scaleFactor);
        return glm::translate(glm::mat4(1.0f), finalPosition);
    }

    glm::mat4 Bone::interpolateRotation(float animationTime) {
        if (1 == rotationsCount) {
            auto rotation = glm::normalize(rotations[0].rotation);
            return glm::toMat4(rotation);
        }

        unsigned int p0Index = getRotationIndex(animationTime);
        unsigned int p1Index = p0Index + 1;
        float scaleFactor = getScaleFactor(rotations[p0Index].timeStamp,
                                           rotations[p1Index].timeStamp, animationTime);
        glm::quat finalRotation = glm::slerp(rotations[p0Index].rotation, rotations[p1Index].rotation,
                                             scaleFactor);
        finalRotation = glm::normalize(finalRotation);
        return glm::toMat4(finalRotation);
    }

    glm::mat4 Bone::interpolateScale(float animationTime) {
        if (1 == scalesCount)
            return glm::scale(glm::mat4(1.0f), scales[0].scale);

        unsigned int p0Index = getScaleIndex(animationTime);
        unsigned int p1Index = p0Index + 1;
        float scaleFactor = getScaleFactor(scales[p0Index].timeStamp,
                                           scales[p1Index].timeStamp, animationTime);
        glm::vec3 finalScale = glm::mix(scales[p0Index].scale, scales[p1Index].scale, scaleFactor);
        return glm::scale(glm::mat4(1.0f), finalScale);
    }

    void Bone::update(float animationTime) {
        glm::mat4 translation = interpolatePosition(animationTime);
        glm::mat4 rotation = interpolateRotation(animationTime);
        glm::mat4 scale = interpolateScale(animationTime);
        transform = translation * rotation * scale;
    }
}

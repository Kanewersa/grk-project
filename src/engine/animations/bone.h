#pragma once

#include <vector>
#include <assimp/scene.h>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <stdexcept>
#include "../../utils.h"

namespace zombies {
    struct BoneInfo {
        int id;
        glm::mat4 offset;
    };

    struct KeyFramePosition {
        glm::vec3 position;
        float timeStamp;
    };

    struct KeyFrameRotation {
        glm::quat rotation;
        float timeStamp;
    };

    struct KeyFrameScale {
        glm::vec3 scale;
        float timeStamp;
    };

    class Bone {
    public:
        Bone(const std::string &name, int id, const aiNodeAnim *nodeAnim);

        void update(float animationTime);

        int getId() const { return id; }

        std::string getName() const { return name; }

        glm::mat4 getLocalTransform() { return transform; }

        unsigned int getPositionIndex(float animationTime) {
            for (unsigned int index = 0; index < positionsCount - 1; ++index) {
                if (animationTime < positions[index + 1].timeStamp) {
                    return index;
                }
            }
            throw std::runtime_error("Could not get position index for timestamp.");
        }

        unsigned int getRotationIndex(float animationTime) {
            for (unsigned int index = 0; index < rotationsCount - 1; ++index) {
                if (animationTime < rotations[index + 1].timeStamp)
                    return index;
            }
            throw std::runtime_error("Could not get rotation index for timestamp.");
        }

        unsigned int getScaleIndex(float animationTime) {
            for (unsigned int index = 0; index < scalesCount - 1; ++index) {
                if (animationTime < scales[index + 1].timeStamp)
                    return index;
            }
            throw std::runtime_error("Could not get scale index for timestamp.");
        }


    private:
        static float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

        glm::mat4 interpolatePosition(float animationTime);

        glm::mat4 interpolateRotation(float animationTime);

        glm::mat4 interpolateScale(float animationTime);

        std::vector<KeyFramePosition> positions;
        std::vector<KeyFrameRotation> rotations;
        std::vector<KeyFrameScale> scales;
        unsigned int positionsCount;
        unsigned int rotationsCount;
        unsigned int scalesCount;

        int id;
        std::string name;
        glm::mat4 transform;
    };
}

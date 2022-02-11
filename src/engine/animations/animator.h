#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "animation.h"
#include "bone.h"
#include <chrono>

namespace zombies {
    class Animator {
    public:
        explicit Animator(Animation *current);

        void update(float deltaTime);

        void playAnimation(Animation *pAnimation);

        void initializeTransforms(const AssimpNodeData *node, glm::mat4 parentTransform);

        void calculateBoneTransform(const AssimpNodeData *node, glm::mat4 parentTransform);

        std::vector<glm::mat4> getPoseTransforms() {
            return transforms;
        }

        Animation *getCurrentAnimation() {
            return currentAnimation;
        }

        void changeAnimationSpeed(float speed) {
            playSpeed = speed;
        }

    private:
        float playSpeed;
        float currentTime;
        Animation *currentAnimation;
        std::vector<glm::mat4> transforms;
    };

}

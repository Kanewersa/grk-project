#pragma once

#include<assimp/quaternion.h>
#include<assimp/vector3.h>
#include<assimp/matrix4x4.h>
#include <assimp/scene.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class Utils {
public:
    static glm::mat4 GetGlmMatrix(const aiMatrix4x4 &matrix) {
        // Swap rows with columns
        return glm::mat4{
                matrix.a1, matrix.b1, matrix.c1, matrix.d1,
                matrix.a2, matrix.b2, matrix.c2, matrix.d2,
                matrix.a3, matrix.b3, matrix.c3, matrix.d3,
                matrix.a4, matrix.b4, matrix.c4, matrix.d4
        };
    }

    static glm::mat4 FixMatrixRotation(glm::mat4 rotation) {
        return glm::rotate(rotation, glm::radians(-90.0f), {1, 0, 0});
    }

    static glm::vec3 GetGlmVec(const aiVector3D &vec) {
        return {vec.x, vec.y, vec.z};
    }

    static glm::quat GetGlmQuat(const aiQuaternion &quaternion) {
        return {quaternion.w, quaternion.x, quaternion.y, quaternion.z};
    }

    static glm::vec3 RotationToVector(float rotation) {
        return {sin(glm::radians(rotation)), 0, cos(glm::radians(rotation))};
    }

    // Returns random float between 0.0 and 1.0 (inclusive)
    static float RandomFloat() {
        return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
};
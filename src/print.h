#pragma once

#include <iostream>
#include "glm/ext/matrix_float4x4.hpp"
#include "assimp/matrix4x4.h"

namespace zombies {
    static void print(glm::mat4 matrix) {
        for (int x = 0; x < 4; x++) {
            std::cout << "[ ";
            for (int y = 0; y < 4; y++) {
                std::cout << matrix[x][y] << " ";
            }
            std::cout << "]" << std::endl;
        }
    }

    static void print(aiMatrix4x4 matrix) {
        for (int x = 0; x < 4; x++) {
            std::cout << "[ ";
            for (int y = 0; y < 4; y++) {
                std::cout << matrix[x][y] << " ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << std::endl;
    }
}

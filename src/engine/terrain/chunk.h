#pragma once

#include <string>
#include "gl.h"
#include "glm/vec2.hpp"

namespace zombies {
    class Chunk {
    public:
        static const int WIDTH = 127;
        static const int HEIGHT = 127;

        static std::string GetPositionKey(int x, int y) {
            return std::string("{") + std::to_string(x) + std::string(", ") + std::to_string(y) + std::string(")");
        }
    };
}
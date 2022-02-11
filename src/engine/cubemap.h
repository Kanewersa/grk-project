#pragma once

#include <vector>
#include <string>

namespace zombies {
    class Cubemap {
    public:
        Cubemap(std::vector<std::string> faces);

        unsigned int getTexture() const {
            return cubemapTexture;
        }

    private:
        unsigned int load(std::vector<std::string> faces);
        unsigned int cubemapTexture;
    };
}
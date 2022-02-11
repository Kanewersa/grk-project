#pragma once

#include "../../engine/animations/model.h"

namespace zombies {
    struct AnimatedModelComponent {
    public:
        Model model;
        Animation animation;
    };
}
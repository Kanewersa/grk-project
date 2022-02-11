#pragma once

#include <unordered_map>
#include "animations/model.h"

namespace zombies {
    enum ModelType {
        BubbleModel,
        Flower,
        BigAlgae,
        Shark,
        Fish,
        CoralFish,
        SpecialFish,

        SmallAlgae,
        SmallRedAlgae,
        SmallBlueAlgae,
        SmallYellowAlgae,
        SmallPurpleAlgae,

        MediumAlgae,
        MediumBlueAlgae,
        MediumYellowAlgae,
        MediumRedAlgae,
        MediumPurpleAlgae,
    };

    class ModelManager {
    public:
        static ModelManager &Instance() {
            static ModelManager instance;
            return instance;
        }

        ModelManager(ModelManager const &) = delete;

        void operator=(ModelManager const &) = delete;

        static Model &GetModel(ModelType modelType);

    private:
        ModelManager();

        std::unordered_map<ModelType, std::unique_ptr<Model>> models;
    };
}

#include "model_manager.h"

namespace zombies {

    ModelManager::ModelManager() {
        models[ModelType::Flower] = std::make_unique<Model>("models/plants/Glony.obj");

        models[ModelType::SmallAlgae] = std::make_unique<Model>("models/plants/GlonPatyczak.obj");
        models[ModelType::SmallRedAlgae] = std::make_unique<Model>("models/plants/red/GlonPatyczak.obj");
        models[ModelType::SmallBlueAlgae] = std::make_unique<Model>("models/plants/blue/GlonPatyczak.obj");
        models[ModelType::SmallYellowAlgae] = std::make_unique<Model>("models/plants/yellow/GlonPatyczak.obj");
        models[ModelType::SmallPurpleAlgae] = std::make_unique<Model>("models/plants/purple/GlonPatyczak.obj");

        models[ModelType::MediumAlgae] = std::make_unique<Model>("models/plants/Glony2.obj");
        models[ModelType::MediumBlueAlgae] = std::make_unique<Model>("models/plants/blue/Glony2.obj");
        models[ModelType::MediumRedAlgae] = std::make_unique<Model>("models/plants/red/Glony2.obj");
        models[ModelType::MediumYellowAlgae] = std::make_unique<Model>("models/plants/yellow/Glony2.obj");
        models[ModelType::MediumPurpleAlgae] = std::make_unique<Model>("models/plants/purple/Glony2.obj");

        models[ModelType::BigAlgae] = std::make_unique<Model>("models/plants/Glony.obj");
        models[ModelType::Shark] = std::make_unique<Model>("models/shark/shark.dae");
        models[ModelType::BubbleModel] = std::make_unique<Model>("models/bubble.obj");
        models[ModelType::Fish] = std::make_unique<Model>("models/fish.obj");
        models[ModelType::SpecialFish] = std::make_unique<Model>("models/coralfish/fishobj.obj");
        models[ModelType::CoralFish] = std::make_unique<Model>("models/specialfish/fish.obj");
    }

    Model &ModelManager::GetModel(ModelType modelType) {
        return *Instance().models[modelType];
    }
}
#pragma once
#include "../include/DrawableObject.h"
#include "../include/Renderer.h"
#include "../include/Point2D.h"
#include "../include/GameConfig.h"
#include <cstdlib>
#include <ctime>

namespace game {
    class Starfield : public engine2d::DrawableObject {
    public:
        void draw(engine2d::Renderer& r) override;
    };
}
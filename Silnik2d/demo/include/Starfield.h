#pragma once
#include "../include/DrawableObject.h"
#include "../include/Renderer.h"
#include "../include/Point2D.h"
#include <vector>

namespace game {
    class Starfield : public engine2d::DrawableObject {
    private:
        std::vector<engine2d::Point2D> stars;
    public:
        Starfield();
        void draw(engine2d::Renderer& r) override;
    };
}
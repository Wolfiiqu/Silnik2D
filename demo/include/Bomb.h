#pragma once
#include "../include/Circle.h"
#include "../include/UpdatableObject.h"

namespace game {
    class Bomb : public engine2d::Circle, public engine2d::UpdatableObject {
        float elapsed = 0.0f;
        bool exploded = false;
        float explosionElapsed = 0.0f;
        bool offBoard = false;
        float speedMult = 1.0f;

    public:
        Bomb(float x, float y, float speedMult = 1.0f);
        void update(float dt) override;

        bool isDead() const;
        bool isAlive() const override { return !isDead(); }
        bool hasExploded() const { return exploded; }
        float getExplosionProgress() const;
        engine2d::Point2D getCenter() const;
        bool explosionHits(const engine2d::Point2D& p, float r) const;
        void draw(engine2d::Renderer& r) override;
    };
}
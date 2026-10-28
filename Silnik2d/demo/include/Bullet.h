#pragma once
/**
 * @file Bullet.hpp
 * @brief Bazowa klasa pocisku.
 */

#include "../include/Circle.h"
#include "../include/UpdatableObject.h"

namespace game {

    class Bullet : public engine2d::Circle,
                   public engine2d::UpdatableObject {
    protected:
        engine2d::Point2D velocity;
        float lifetime = 0.0f;
        bool dead = false;
        bool offBoard = false;

    public:
        Bullet(float x, float y, engine2d::Point2D vel, engine2d::Color c);
        void update(float dt) override;

        bool isDead() const { return dead; }
        bool isOffBoard() const { return offBoard; }
        engine2d::Point2D getCenter() const;
        bool collidesWith(const engine2d::Point2D& p, float r) const;
    };

} // namespace game
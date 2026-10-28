#pragma once
/**
 * @file Player.h
 * @brief Gracz sterowany WSAD, pięciokątny hitbox, i-frames.
 */

#include "../include/Rectangle.h"
#include "../include/UpdatableObject.h"
#include "../include/InputManager.h"
#include <array>

#include "Polygon.h"

namespace game {

    class Player : public engine2d::Polygon,
                   public engine2d::UpdatableObject {
        engine2d::InputManager* input;

        int lives = 3;
        float invincibleTime = 0.0f;
        bool visibleBlink = true;
        float blinkTimer = 0.0f;

    public:
        Player(float x, float y, engine2d::InputManager* in);
        void update(float dt) override;

        engine2d::Point2D getCenter() const;

        int getLives() const { return lives; }
        bool isInvincible() const { return invincibleTime > 0.0f; }
        bool isVisibleBlink() const { return visibleBlink; }

        bool takeDamage();

        std::array<engine2d::Point2D, 5> getHitbox() const;
        bool hitboxContains(const engine2d::Point2D& p) const;
        bool hitboxCollidesCircle(const engine2d::Point2D& center, float r) const;

        void draw(engine2d::Renderer& r) override;
        void reset();

    private:
        static std::vector<engine2d::Point2D> makePentagon(float cx, float cy, float r);
    };

}
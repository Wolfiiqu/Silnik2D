#pragma once
#include "../include/SpriteObject.h"
#include "../include/UpdatableObject.h"
#include "../include/InputManager.h"
#include <array>
#include <vector>

namespace game {


    enum class Direction { UP, DOWN, LEFT, RIGHT };

    class Player : public engine2d::SpriteObject,
                   public engine2d::UpdatableObject {
        engine2d::InputManager* input;

        int lives = 3;
        float invincibleTime = 0.0f;
        bool visibleBlink = true;
        float blinkTimer = 0.0f;

        Direction currentDir = Direction::UP;
        std::vector<engine2d::Bitmap*> ownedBitmaps;

        bool usingRealAssets = false;

    public:
        Player(float x, float y, engine2d::InputManager* in);
        ~Player();

        void update(float dt) override;

        engine2d::Point2D getCenter() const;

        int getLives() const { return lives; }
        bool isInvincible() const { return invincibleTime > 0.0f; }
        bool isVisibleBlink() const { return visibleBlink; }

        bool takeDamage();


        std::vector<engine2d::Point2D> getHitbox() const;
        bool hitboxContains(const engine2d::Point2D& p) const;
        bool hitboxCollidesCircle(const engine2d::Point2D& center, float r) const;

        void draw(engine2d::Renderer& r) override;
        void reset();

    private:

        void updateSpriteForDirection();
        bool showHitbox = false;
    };

}
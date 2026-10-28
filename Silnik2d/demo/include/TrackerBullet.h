#pragma once
/**
 * @file TrackerBullet.hpp
 * @brief Pocisk śledzący gracza przez X sekund, potem lecący prosto.
 */

#include "../demo/include/Bullet.h"
#include "../demo/include/Player.h"

namespace game {

    class TrackerBullet : public Bullet {
        Player* target;
        float trackTime;
        float elapsed = 0.0f;
    public:
        TrackerBullet(float x, float y, engine2d::Point2D initialTarget,
                      Player* player, float trackSeconds = 2.0f);

        void update(float dt) override;
    };

} // namespace game
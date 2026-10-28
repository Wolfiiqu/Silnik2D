#include "../demo/include/TrackerBullet.h"
#include "../demo/include/GameConfig.h"
#include "../include/MathUtils.h"
#include <cmath>

namespace game {
    using namespace engine2d;

    TrackerBullet::TrackerBullet(float x, float y, Point2D initialTarget,
                                 Player* player, float trackSeconds)
        : Bullet(x, y, {0, 0}, Color(200, 0, 255)),
          target(player), trackTime(trackSeconds) {
        float dx = initialTarget.x - x;
        float dy = initialTarget.y - y;
        float len = std::sqrt(dx*dx + dy*dy);
        if (len > 1e-3f) {
            velocity.x = dx / len * GameConfig::BULLET_SPEED;
            velocity.y = dy / len * GameConfig::BULLET_SPEED;
        }
    }

    void TrackerBullet::update(float dt) {
        if (dead) return;
        elapsed += dt;

        if (elapsed < trackTime && target) {
            Point2D p = getCenter();
            Point2D t = target->getCenter();
            float dx = t.x - p.x;
            float dy = t.y - p.y;
            float len = std::sqrt(dx*dx + dy*dy);
            if (len > 1e-3f) {
                velocity.x = dx / len * GameConfig::BULLET_SPEED;
                velocity.y = dy / len * GameConfig::BULLET_SPEED;
            }
        }

        Bullet::update(dt);
    }

} // namespace game
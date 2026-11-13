#include "../demo/include/HomingBullet.h"
#include "../demo/include/GameConfig.h"
#include "../include/MathUtils.h"
#include <cmath>

namespace game {
    using namespace engine2d;

    HomingBullet::HomingBullet(float x, float y, Point2D target)
        : Bullet(x, y, {0, 0}, Color(255, 100, 0)) {
        float dx = target.x - x;
        float dy = target.y - y;
        float len = std::sqrt(dx*dx + dy*dy);
        if (len < 1e-3f) return;
        velocity.x = dx / len * GameConfig::BULLET_SPEED;
        velocity.y = dy / len * GameConfig::BULLET_SPEED;
    }

} // namespace game
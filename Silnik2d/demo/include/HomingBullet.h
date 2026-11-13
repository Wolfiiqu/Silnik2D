#pragma once
/**
 * @file HomingBullet.hpp
 * @brief Pocisk lecący do pozycji gracza z momentu wystrzału.
 */

#include "Bullet.h"

namespace game {

    class HomingBullet : public Bullet {
    public:
        HomingBullet(float x, float y, engine2d::Point2D target);
    };

} // namespace game
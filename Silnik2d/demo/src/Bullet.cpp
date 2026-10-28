#include "../demo/include/Bullet.h"
#include "../demo/include/GameConfig.h"
#include "../include/Board.h"
#include "../include/MathUtils.h"
#include <cmath>

namespace game {
    using namespace engine2d;

    Bullet::Bullet(float x, float y, Point2D vel, Color c)
        : Circle(GameConfig::BULLET_RADIUS), velocity(vel) {
        setColor(c);
        setFilled(true);
        translate(x - GameConfig::BULLET_RADIUS, y - GameConfig::BULLET_RADIUS);
    }

    void Bullet::update(float dt) {
        if (dead) return;

        translate(velocity.x * dt, velocity.y * dt);
        lifetime += dt;

        Point2D p = getTransform().apply({0, 0});
        float cx = p.x + GameConfig::BULLET_RADIUS;
        float cy = p.y + GameConfig::BULLET_RADIUS;

        // === Sprawdź, czy poza planszą ===
        offBoard = !Board::contains(cx, cy);

        // === Ukryj, jeśli poza planszą ===
        setVisible(!offBoard);

        // === Usuń dopiero po BULLET_LIFETIME ===
        if (lifetime >= GameConfig::BULLET_LIFETIME) dead = true;
    }

    Point2D Bullet::getCenter() const {
        Point2D p = getTransform().apply({0, 0});
        return {p.x + GameConfig::BULLET_RADIUS, p.y + GameConfig::BULLET_RADIUS};
    }

    bool Bullet::collidesWith(const Point2D& p, float r) const {
        if (offBoard) return false;   // poza planszą nie koliduje
        Point2D c = getCenter();
        float dx = c.x - p.x;
        float dy = c.y - p.y;
        float dist = std::sqrt(dx*dx + dy*dy);
        return dist < (GameConfig::BULLET_RADIUS + r + GameConfig::COLLISION_MARGIN);
    }

}
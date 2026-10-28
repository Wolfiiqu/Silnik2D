#include "../demo/include/Bomb.h"
#include "../demo/include/GameConfig.h"
#include <cmath>

#include "Renderer.h"

namespace game {
using namespace engine2d;

Bomb::Bomb(float x, float y) : Circle(GameConfig::BOMB_RADIUS) {
    setColor(Color(255, 255, 0));
    setFilled(true);
    translate(x - GameConfig::BOMB_RADIUS, y - GameConfig::BOMB_RADIUS);
}
    void Bomb::draw(Renderer& r) {
    if (!exploded) {
        Circle::draw(r);
        return;
    }
    // Wybuch: koło o rosnącym promieniu, malejącej alpha
    float t = getExplosionProgress();
    if (t >= 1.0f) return;
    float radius = GameConfig::BOMB_EXPLODE_RADIUS * t;
    unsigned char alpha = (unsigned char)(255 * (1.0f - t));
    Point2D c = getCenter();
    // Rysujemy 3 koncentryczne koła (ładniejszy efekt)
    r.drawCircle(c, (int)radius, Color(255, 200, 0, alpha));
    r.drawCircle(c, (int)(radius * 0.7f), Color(255, 100, 0, alpha));
    r.drawCircle(c, (int)(radius * 0.4f), Color(255, 255, 255, alpha));
}

void Bomb::update(float dt) {
    if (!exploded) {
        // === Spadanie ===
        translate(0, GameConfig::BOMB_FALL_SPEED * dt);
        elapsed += dt;

        // === Animacja koloru: żółty → czerwony ===
        float t = elapsed / GameConfig::BOMB_FUSE;
        if (t > 1.0f) t = 1.0f;
        setColor(Color(255, (unsigned char)(255 * (1.0f - t)), 0));

        // === Sprawdź, czy bomba wyleciała POD planszę ===
        Point2D p = getTransform().apply({0, 0});
        float cy = p.y + GameConfig::BOMB_RADIUS;
        if (cy > GameConfig::BOARD_Y + GameConfig::BOARD_H) {
            // Wybuchła poza planszą — od razu usuń
            exploded = true;
            explosionElapsed = GameConfig::BOMB_EXPLODE_TIME;  // "skończony" wybuch
            return;
        }

        // === Czas minął → wybuch ===
        if (elapsed >= GameConfig::BOMB_FUSE) {
            exploded = true;
            explosionElapsed = 0.0f;
        }
    } else {
        explosionElapsed += dt;
    }
}

bool Bomb::isDead() const {
    // Usuń, gdy wybuch się skończył (albo bomba wyleciała poza planszę)
    return exploded && explosionElapsed >= GameConfig::BOMB_EXPLODE_TIME;
}

float Bomb::getExplosionProgress() const {
    float t = explosionElapsed / GameConfig::BOMB_EXPLODE_TIME;
    return (t > 1.0f) ? 1.0f : t;
}

Point2D Bomb::getCenter() const {
    Point2D p = getTransform().apply({0, 0});
    return {p.x + GameConfig::BOMB_RADIUS, p.y + GameConfig::BOMB_RADIUS};
}

bool Bomb::explosionHits(const Point2D& p, float r) const {
    if (!exploded) return false;
    Point2D c = getCenter();
    float radius = GameConfig::BOMB_EXPLODE_RADIUS * getExplosionProgress();
    float dx = c.x - p.x;
    float dy = c.y - p.y;
    float dist = std::sqrt(dx*dx + dy*dy);
    return dist < (radius + r + GameConfig::COLLISION_MARGIN);
}

}

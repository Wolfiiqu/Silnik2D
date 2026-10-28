#include "../demo/include/Player.h"
#include "../demo/include/GameConfig.h"
#include "../demo/include/Board.h"
#include "../include/MathUtils.h"
#include <cmath>
#include <algorithm>

namespace game {
using namespace engine2d;

std::vector<Point2D> Player::makePentagon(float cx, float cy, float r) {
    std::vector<Point2D> pts;
    for (int i = 0; i < 5; ++i) {
        float a = -3.14159f / 2 + i * 2 * 3.14159f / 5;
        pts.push_back({cx + r * std::cos(a), cy + r * std::sin(a)});
    }
    return pts;
}

Player::Player(float x, float y, InputManager* in)
    : Polygon(makePentagon(GameConfig::PLAYER_SIZE / 2, GameConfig::PLAYER_SIZE / 2,
                           GameConfig::PLAYER_SIZE / 2)),
      input(in), lives(GameConfig::PLAYER_LIVES) {
    setColor(Color(0, 200, 255));
    setFilled(true);
    translate(x, y);
}

void Player::update(float dt) {
    if (invincibleTime > 0.0f) {
        invincibleTime -= dt;
        blinkTimer += dt;
        visibleBlink = (std::fmod(blinkTimer, 0.2f) < 0.1f);
        if (invincibleTime <= 0.0f) {
            invincibleTime = 0.0f;
            visibleBlink = true;
            blinkTimer = 0.0f;
        }
    }

    float dx = 0, dy = 0;
    if (input->isKeyDown(sf::Keyboard::A)) dx -= 1;
    if (input->isKeyDown(sf::Keyboard::D)) dx += 1;
    if (input->isKeyDown(sf::Keyboard::W)) dy -= 1;
    if (input->isKeyDown(sf::Keyboard::S)) dy += 1;
    if (dx == 0 && dy == 0) return;

    float len = std::sqrt(dx*dx + dy*dy);
    dx /= len; dy /= len;

    translate(dx * GameConfig::PLAYER_SPEED * dt,
              dy * GameConfig::PLAYER_SPEED * dt);

    Point2D p = getTransform().apply({0, 0});
    float x = p.x, y = p.y;
    Board::clamp(x, y, GameConfig::PLAYER_SIZE, GameConfig::PLAYER_SIZE);
    translate(x - p.x, y - p.y);
}

Point2D Player::getCenter() const {
    Point2D p = getTransform().apply({0, 0});
    return {p.x + GameConfig::PLAYER_SIZE / 2,
            p.y + GameConfig::PLAYER_SIZE / 2};
}

std::array<Point2D, 5> Player::getHitbox() const {
    Point2D c = getCenter();
    float R = GameConfig::PLAYER_SIZE / 2;
    std::array<Point2D, 5> pts;
    for (int i = 0; i < 5; ++i) {
        float a = -3.14159f / 2 + i * 2 * 3.14159f / 5;
        pts[i] = {c.x + R * std::cos(a), c.y + R * std::sin(a)};
    }
    return pts;
}

bool Player::hitboxContains(const Point2D& p) const {
    auto pts = getHitbox();
    bool inside = false;
    for (int i = 0, j = 4; i < 5; j = i++) {
        if (((pts[i].y > p.y) != (pts[j].y > p.y)) &&
            (p.x < (pts[j].x - pts[i].x) * (p.y - pts[i].y) / (pts[j].y - pts[i].y) + pts[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}

bool Player::hitboxCollidesCircle(const Point2D& center, float r) const {
    if (hitboxContains(center)) return true;

    auto pts = getHitbox();
    for (auto& p : pts) {
        float dx = p.x - center.x;
        float dy = p.y - center.y;
        if (dx*dx + dy*dy < r*r) return true;
    }

    for (int i = 0; i < 5; ++i) {
        Point2D a = pts[i];
        Point2D b = pts[(i + 1) % 5];
        float abx = b.x - a.x, aby = b.y - a.y;
        float apx = center.x - a.x, apy = center.y - a.y;
        float t = (apx * abx + apy * aby) / (abx * abx + aby * aby);
        if (t < 0) t = 0;
        if (t > 1) t = 1;
        float cx = a.x + t * abx;
        float cy = a.y + t * aby;
        float dx = center.x - cx, dy = center.y - cy;
        if (dx*dx + dy*dy < r*r) return true;
    }
    return false;
}

bool Player::takeDamage() {
    if (isInvincible()) return false;
    lives--;
    invincibleTime = GameConfig::INVINCIBILITY_TIME;
    blinkTimer = 0.0f;
    return true;
}

void Player::reset() {
    lives = GameConfig::PLAYER_LIVES;
    invincibleTime = 0.0f;
    visibleBlink = true;
    blinkTimer = 0.0f;
}

void Player::draw(Renderer& r) {
    if (!visibleBlink) return;
    Polygon::draw(r);
}

}
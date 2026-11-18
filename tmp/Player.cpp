#include "../demo/include/Player.h"
#include "../demo/include/GameConfig.h"
#include "../demo/include/Board.h"
#include "../include/MathUtils.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

namespace game {
using namespace engine2d;

Player::Player(float x, float y, InputManager* in)
    : input(in), lives(GameConfig::PLAYER_LIVES), currentDir(Direction::UP) {

    if (!input) {
        std::cerr << "BLAD: InputManager jest nullptr w konstruktorze Player!\n";
    }

    Color colors[4] = { Color(0, 200, 255), Color(0, 150, 255), Color(100, 100, 255), Color(0, 255, 200) };
    std::string dirNames[4] = { "up", "down", "left", "right" };

    auto tryLoad = [&](const std::string& path, Color fallbackColor) {
        Bitmap* b = new Bitmap();
        if (b->loadFromFile(path)) {
            std::cout << "Zaladowano: " << path << "\n";
            usingRealAssets = true;
        } else {
            b->createProcedural(40, 40, fallbackColor);
        }
        ownedBitmaps.push_back(b);
        addFrame(b);
    };

    // Wczytujemy po 6 klatek dla każdego z 4 kierunków (razem 24 pliki)
    for (int i = 0; i < 4; ++i) {
        for (int frame = 0; frame < 6; ++frame) {
            Color c = colors[i];
            if (frame > 0) {
                c.r = std::min(255, c.r + frame * 10);
                c.g = std::min(255, c.g + frame * 10);
            }

            std::string path = "assets/player_" + dirNames[i] + "_" + std::to_string(frame + 1) + ".png";
            tryLoad(path, c);
        }
    }

    setFrameTime(0.08f); // Optymalny czas klatki dla 6 klatek animacji
    updateSpriteForDirection();
    translate(x, y);
}

Player::~Player() {
    for (auto* b : ownedBitmaps) {
        delete b;
    }
}

void Player::update(float dt) {
    if (!input) return;

    if (input->isKeyJustPressed(sf::Keyboard::H)) {
        showHitbox = !showHitbox;
    }
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

    if (dx != 0 || dy != 0) {
        float len = std::sqrt(dx*dx + dy*dy);
        dx /= len; dy /= len;

        if (dx < 0) currentDir = Direction::LEFT;
        else if (dx > 0) currentDir = Direction::RIGHT;
        else if (dy < 0) currentDir = Direction::UP;
        else if (dy > 0) currentDir = Direction::DOWN;

        updateSpriteForDirection();

        translate(dx * GameConfig::PLAYER_SPEED * dt, dy * GameConfig::PLAYER_SPEED * dt);

        Point2D p = getTransform().apply({0, 0});
        float x = p.x, y = p.y;
        Board::clamp(x, y, GameConfig::PLAYER_SIZE, GameConfig::PLAYER_SIZE);
        translate(x - p.x, y - p.y);

        // Obsługa animacji dla 6 klatek
        elapsed += dt;
        if (elapsed >= frameTime) {
            elapsed -= frameTime;
            int baseIndex = static_cast<int>(currentDir) * 6;
            currentFrame++;
            if (currentFrame >= baseIndex + 6 || currentFrame < baseIndex) {
                currentFrame = baseIndex;
            }

            // Bezpieczne przypisanie klatki zapobiegające awarii
            if (currentFrame >= 0 && currentFrame < static_cast<int>(frames.size())) {
                bitmap = frames[currentFrame];
            }
        }
    } else {
        elapsed = 0.0f;
        updateSpriteForDirection();
    }
}

void Player::updateSpriteForDirection() {
    int baseIndex = static_cast<int>(currentDir) * 6;
    currentFrame = baseIndex;
    if (currentFrame >= 0 && currentFrame < static_cast<int>(frames.size())) {
        bitmap = frames[currentFrame];
    }
}

Point2D Player::getCenter() const {
    Point2D p = getTransform().apply({0, 0});
    return {p.x + GameConfig::PLAYER_SIZE / 2, p.y + GameConfig::PLAYER_SIZE / 2};
}

std::vector<Point2D> Player::getHitbox() const {
    Point2D c = getCenter();
    std::vector<Point2D> pts;

    float R = GameConfig::PLAYER_SIZE / 2;
    for (int i = 0; i < 5; ++i) {
        float a = -3.14159f / 2 + i * 2 * 3.14159f / 5;
        pts.push_back({c.x + R * std::cos(a), c.y + R * std::sin(a)});
    }

    return pts;
}

bool Player::hitboxContains(const Point2D& p) const {
    auto pts = getHitbox();
    bool inside = false;
    for (size_t i = 0, j = pts.size() - 1; i < pts.size(); j = i++) {
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

    for (size_t i = 0; i < pts.size(); ++i) {
        Point2D a = pts[i];
        Point2D b = pts[(i + 1) % pts.size()];
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
    currentDir = Direction::UP;
    updateSpriteForDirection();
}

void Player::draw(Renderer& r) {
    if (!visibleBlink) return;

    if (usingRealAssets) {
        if (bitmap) {
            BitmapObject::draw(r);
        }
    } else {
        Color c(0, 0, 0);
        if (bitmap) {
            c = bitmap->getPixel(0, 0);
        }

        Point2D p1 = getTransform().apply({0, 0});
        Point2D p2 = getTransform().apply({40, 0});
        Point2D p3 = getTransform().apply({40, 40});
        Point2D p4 = getTransform().apply({0, 40});

        std::vector<Point2D> pts = {p1, p2, p3, p4};
        r.scanlineFill(pts, c);
    }

    if (showHitbox) {
        auto hitboxPts = getHitbox();
        Color debugColor(0, 255, 0);

        for (size_t i = 0; i < hitboxPts.size(); ++i) {
            size_t next = (i + 1) % hitboxPts.size();
            r.drawLine(hitboxPts[i], hitboxPts[next], debugColor);
        }
    }
}
}
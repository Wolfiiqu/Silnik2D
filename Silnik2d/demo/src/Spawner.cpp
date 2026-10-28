#include "../demo/include/Spawner.h"
#include "../demo/include/GameConfig.h"
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace game {
using namespace engine2d;

Spawner::Spawner(Engine& eng, Player* p) : engine(eng), player(p) {}

void Spawner::spawnHoming() {
    float side = (float)(std::rand() % 4);
    float x, y;
    if (side == 0) { x = GameConfig::BOARD_X + GameConfig::BOARD_W + 20; y = GameConfig::BOARD_Y + std::rand() % (int)GameConfig::BOARD_H; }
    else if (side == 1) { x = GameConfig::BOARD_X - 20; y = GameConfig::BOARD_Y + std::rand() % (int)GameConfig::BOARD_H; }
    else if (side == 2) { x = GameConfig::BOARD_X + std::rand() % (int)GameConfig::BOARD_W; y = GameConfig::BOARD_Y - 20; }
    else { x = GameConfig::BOARD_X + std::rand() % (int)GameConfig::BOARD_W; y = GameConfig::BOARD_Y + GameConfig::BOARD_H + 20; }

    Point2D target = player->getCenter();
    auto b = std::make_unique<HomingBullet>(x, y, target);
    homingBullets.push_back(b.get());
    engine.addObject(std::move(b));
}

void Spawner::spawnTracker() {
    float side = (float)(std::rand() % 4);
    float x, y;
    if (side == 0) { x = GameConfig::BOARD_X + GameConfig::BOARD_W + 20; y = GameConfig::BOARD_Y + std::rand() % (int)GameConfig::BOARD_H; }
    else if (side == 1) { x = GameConfig::BOARD_X - 20; y = GameConfig::BOARD_Y + std::rand() % (int)GameConfig::BOARD_H; }
    else if (side == 2) { x = GameConfig::BOARD_X + std::rand() % (int)GameConfig::BOARD_W; y = GameConfig::BOARD_Y - 20; }
    else { x = GameConfig::BOARD_X + std::rand() % (int)GameConfig::BOARD_W; y = GameConfig::BOARD_Y + GameConfig::BOARD_H + 20; }

    Point2D target = player->getCenter();
    auto b = std::make_unique<TrackerBullet>(x, y, target, player);
    trackerBullets.push_back(b.get());
    engine.addObject(std::move(b));
}

void Spawner::spawnBomb() {
    float x = GameConfig::BOARD_X + std::rand() % (int)GameConfig::BOARD_W;
    float y = GameConfig::BOARD_Y - 40;
    auto b = std::make_unique<Bomb>(x, y);
    bombs.push_back(b.get());
    engine.addObject(std::move(b));
}

    void Spawner::update(float dt) {
    homingTimer += dt;
    trackerTimer += dt;
    bombTimer += dt;

    if (homingTimer >= GameConfig::HOMING_INTERVAL) { homingTimer = 0; spawnHoming(); }
    if (trackerTimer >= GameConfig::TRACKER_INTERVAL) { trackerTimer = 0; spawnTracker(); }
    if (bombTimer >= GameConfig::BOMB_INTERVAL) { bombTimer = 0; spawnBomb(); }

    // === Update wszystkich pocisków (włącznie z bombami po wybuchu) ===
    for (auto* b : homingBullets) b->update(dt);
    for (auto* b : trackerBullets) b->update(dt);
    for (auto* b : bombs) b->update(dt);   // ← musi być

    // === Usuwanie martwych ===
    homingBullets.erase(
        std::remove_if(homingBullets.begin(), homingBullets.end(),
            [](HomingBullet* b) { return b->isDead(); }),
        homingBullets.end());
    trackerBullets.erase(
        std::remove_if(trackerBullets.begin(), trackerBullets.end(),
            [](TrackerBullet* b) { return b->isDead(); }),
        trackerBullets.end());
    bombs.erase(
        std::remove_if(bombs.begin(), bombs.end(),
            [](Bomb* b) { return b->isDead(); }),
        bombs.end());
}
    void Spawner::clear() {
    homingBullets.clear();
    trackerBullets.clear();
    bombs.clear();
}

} // namespace game
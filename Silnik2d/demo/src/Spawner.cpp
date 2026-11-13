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
    b->scaleVelocity(getHomingSpeedMult()); // Limit dla Homing
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
    // Przekazujemy limit prędkości dla Trackera
    auto b = std::make_unique<TrackerBullet>(x, y, target, player, 2.0f, getTrackerSpeedMult());
    trackerBullets.push_back(b.get());
    engine.addObject(std::move(b));
}

void Spawner::spawnBomb() {
    float x = GameConfig::BOARD_X + std::rand() % (int)GameConfig::BOARD_W;
    float y = GameConfig::BOARD_Y - 40;
    // Przekazujemy mnożnik do Bomby
    auto b = std::make_unique<Bomb>(x, y, getBombSpeedMult());
    bombs.push_back(b.get());
    engine.addObject(std::move(b));
}

void Spawner::update(float dt) {
    difficulty += 0.01f * dt; // Płynniejszy wzrost
    homingTimer += dt;
    trackerTimer += dt;
    bombTimer += dt;

    // Używamy getSpawnMult() (limit ilości pocisków)
    if (homingTimer >= GameConfig::HOMING_INTERVAL / getSpawnMult()) { homingTimer = 0; spawnHoming(); }
    if (trackerTimer >= GameConfig::TRACKER_INTERVAL / getSpawnMult()) { trackerTimer = 0; spawnTracker(); }
    if (bombTimer >= GameConfig::BOMB_INTERVAL / getSpawnMult()) { bombTimer = 0; spawnBomb(); }

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
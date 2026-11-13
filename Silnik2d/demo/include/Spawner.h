#pragma once
/**
 * @file Spawner.hpp
 * @brief Zarządza timerami i spawnuje pociski.
 */

#include <vector>
#include <algorithm>
#include "GameConfig.h"
#include "HomingBullet.h"
#include "TrackerBullet.h"
#include "Bomb.h"
#include "Player.h"
#include "../include/Engine.h"

namespace game {

    class Spawner {
        engine2d::Engine& engine;
        Player* player;

        std::vector<HomingBullet*> homingBullets;
        std::vector<TrackerBullet*> trackerBullets;
        std::vector<Bomb*> bombs;

        float homingTimer = 0, trackerTimer = 0, bombTimer = 0;
        float difficulty = 1.0f; // Zaczynamy od 1.0

    private:
        void spawnHoming();
        void spawnTracker();
        void spawnBomb();

    public:
        Spawner(engine2d::Engine& eng, Player* p);
        float getDifficulty() const { return difficulty; }

        // NOWE GETTERY Z LIMITAMI
        float getSpawnMult() const { return std::min(difficulty, GameConfig::MAX_SPAWN_MULT); }
        float getHomingSpeedMult() const { return std::min(difficulty, GameConfig::MAX_HOMING_SPEED_MULT); }
        float getTrackerSpeedMult() const { return std::min(difficulty, GameConfig::MAX_TRACKER_SPEED_MULT); }
        float getBombSpeedMult() const { return std::min(difficulty, GameConfig::MAX_BOMB_SPEED_MULT); }

        void update(float dt);

        const std::vector<HomingBullet*>& getHomingBullets() const { return homingBullets; }
        const std::vector<TrackerBullet*>& getTrackerBullets() const { return trackerBullets; }
        const std::vector<Bomb*>& getBombs() const { return bombs; }

        void clear();
    };

} // namespace game
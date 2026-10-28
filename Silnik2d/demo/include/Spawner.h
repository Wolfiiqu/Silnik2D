#pragma once
/**
 * @file Spawner.hpp
 * @brief Zarządza timerami i spawnuje pociski.
 */

#include <vector>
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
    private:
        void spawnHoming();
        void spawnTracker();
        void spawnBomb();
    public:
        Spawner(engine2d::Engine& eng, Player* p);

        void update(float dt);

        // Dostęp do list (dla kolizji)
        const std::vector<HomingBullet*>& getHomingBullets() const { return homingBullets; }
        const std::vector<TrackerBullet*>& getTrackerBullets() const { return trackerBullets; }
        const std::vector<Bomb*>& getBombs() const { return bombs; }

        void clear();
    };

} // namespace game

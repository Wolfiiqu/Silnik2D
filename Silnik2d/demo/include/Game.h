#pragma once
#include <memory>
#include "../include/Engine.h"
#include "Player.h"
#include "Spawner.h"
#include "HudObject.h"    // ← 1. include

namespace game {

    class Game {
        engine2d::Engine engine;
        Player* player = nullptr;
        Spawner* spawner = nullptr;
        HudObject* hud = nullptr;    // ← 2. pole

        int score = 0;
        float survivalTime = 0.0f;
        bool gameOver = false;

    public:
        Game();
        void run();
        int getScore() const { return score; }
        int getPlayerLives() const { return player ? player->getLives() : 0; }
        bool isGameOver() const { return gameOver; }

    private:
        void onUpdate(float dt);
        void checkCollisions();
        void restart();
    };

}
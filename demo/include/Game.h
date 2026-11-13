#pragma once
#include <memory>
#include "../include/Engine.h"
#include "Player.h"
#include "Spawner.h"
#include "HudObject.h"
#include "MenuScene.h"
#include "GameOverScene.h"


namespace game {

    enum class GameState { MENU, PLAYING, GAMEOVER };

    class Game {
        engine2d::Engine engine;
        Player* player = nullptr;
        Spawner* spawner = nullptr;
        HudObject* hud = nullptr;

        MenuScene* menuScene = nullptr;
        GameOverScene* gameOverScene = nullptr;

        GameState state = GameState::MENU;

        int score = 0;
        float survivalTime = 0.0f;

    public:
        Game();
        ~Game() {
            delete spawner;
            delete hud;
        }


        void setState(GameState s) { state = s; }
        void startGame();
        void goToMenu();
        float getSurvivalTime() const { return survivalTime; }


        void run();
        int getScore() const { return score; }
        int getPlayerLives() const { return player ? player->getLives() : 0; }
        GameState getState() const { return state; }

        bool isGameOver() const { return state == GameState::GAMEOVER; }

    private:
        void onUpdate(float dt);
        void checkCollisions();

    };

}
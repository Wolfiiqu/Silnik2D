#include "..\demo\include\Game.h"
#include "..\demo\include\GameConfig.h"
#include "..\demo\include\BoardObject.h"
#include "..\demo\include\HudObject.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace game {
using namespace engine2d;


    Game::Game()
        : engine(GameConfig::WINDOW_W, GameConfig::WINDOW_H, "Silnik2D - Demo gry") {
        std::srand((unsigned)std::time(nullptr));

        engine.addObject(std::make_unique<BoardObject>());

        auto p = std::make_unique<Player>(
            GameConfig::BOARD_X + GameConfig::BOARD_W / 2 - GameConfig::PLAYER_SIZE / 2,
            GameConfig::BOARD_Y + GameConfig::BOARD_H / 2 - GameConfig::PLAYER_SIZE / 2,
            &engine.getInput());
        player = p.get();
        engine.addObject(std::move(p));

        hud = new HudObject(this);                    // ← 3. new
        engine.setPostRenderCallback([this](sf::RenderWindow& w) {
            hud->draw(w);                             // ← 4. draw
        });

        spawner = new Spawner(engine, player);
    }

void Game::run() {
    engine.setUpdateCallback([this](float dt) { onUpdate(dt); });
    engine.run();
}

void Game::onUpdate(float dt) {
    if (gameOver) {
        if (engine.getInput().isKeyJustPressed(sf::Keyboard::R)) {
            restart();
        }
        return;
    }

    // === PUNKTACJA: czas * 10 ===
    survivalTime += dt;
    score = (int)(survivalTime * GameConfig::SCORE_PER_SECOND);

    // === Logika ===
    spawner->update(dt);
    checkCollisions();
}

void Game::checkCollisions() {
    // Homing
    for (auto* b : spawner->getHomingBullets()) {
        if (b->isDead() || b->isOffBoard()) continue;
        if (player->hitboxCollidesCircle(b->getCenter(), GameConfig::BULLET_RADIUS)) {
            if (player->takeDamage()) {
                std::cout << "Trafiony homing! Zycia: " << player->getLives() << "\n";
                if (player->getLives() <= 0) gameOver = true;
            }
        }
    }
    // Tracker
    for (auto* b : spawner->getTrackerBullets()) {
        if (b->isDead() || b->isOffBoard()) continue;
        if (player->hitboxCollidesCircle(b->getCenter(), GameConfig::BULLET_RADIUS)) {
            if (player->takeDamage()) {
                std::cout << "Trafiony tracker! Zycia: " << player->getLives() << "\n";
                if (player->getLives() <= 0) gameOver = true;
            }
        }
    }
    // Bomby
    for (auto* b : spawner->getBombs()) {
        if (b->isDead() || !b->hasExploded()) continue;
        float radius = GameConfig::BOMB_EXPLODE_RADIUS * b->getExplosionProgress();
        if (player->hitboxCollidesCircle(b->getCenter(), radius)) {
            if (player->takeDamage()) {
                std::cout << "Trafiony wybuchem! Zycia: " << player->getLives() << "\n";
                if (player->getLives() <= 0) gameOver = true;
            }
        }
    }
}

void Game::restart() {
    engine.clearObjects();
    spawner->clear();
    delete spawner;
    delete player;

    score = 0;
    survivalTime = 0.0f;
    gameOver = false;

    // Odtwórz planszę
    engine.addObject(std::make_unique<BoardObject>());

    // Odtwórz gracza
    auto p = std::make_unique<Player>(
        GameConfig::BOARD_X + GameConfig::BOARD_W / 2 - GameConfig::PLAYER_SIZE / 2,
        GameConfig::BOARD_Y + GameConfig::BOARD_H / 2 - GameConfig::PLAYER_SIZE / 2,
        &engine.getInput());
    player = p.get();
    engine.addObject(std::move(p));

    // Odtwórz HUD

    // Odtwórz spawner
    spawner = new Spawner(engine, player);
}

}
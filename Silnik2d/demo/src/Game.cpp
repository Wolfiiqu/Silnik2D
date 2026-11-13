#include "../include/Game.h"
#include "../include/GameConfig.h"
#include "../include/BoardObject.h"
#include "../include/HudObject.h"
#include "../include/MenuScene.h"
#include "../include/GameOverScene.h"
#include "../include/Starfield.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

namespace game {
using namespace engine2d;

    Game::Game()
        : engine(GameConfig::WINDOW_W, GameConfig::WINDOW_H, "Silnik2D - Demo gry") {

        std::srand((unsigned)std::time(nullptr));

        // 1. Tło
        engine.addObject(std::make_unique<Starfield>());

        // 2. Menu
        auto menu = std::make_unique<MenuScene>(this);
        menuScene = menu.get();
        engine.addObject(std::move(menu));

        // 3. HUD i Callback
        hud = new HudObject(this);
        engine.setPostRenderCallback([this](sf::RenderWindow& w) {
            if (state == GameState::MENU && menuScene) {
                menuScene->drawUI(w);
            }
            if (state == GameState::GAMEOVER && gameOverScene) {
                gameOverScene->drawUI(w);
            }
            hud->draw(w);
        });
    }

    void Game::startGame() {
        engine.clearObjects();

        // Tło z gwiazdami w grze
        engine.addObject(std::make_unique<Starfield>());

        // Plansza
        engine.addObject(std::make_unique<BoardObject>());

        // Gracz
        auto p = std::make_unique<Player>(
            GameConfig::BOARD_X + GameConfig::BOARD_W / 2 - GameConfig::PLAYER_SIZE / 2,
            GameConfig::BOARD_Y + GameConfig::BOARD_H / 2 - GameConfig::PLAYER_SIZE / 2,
            &engine.getInput());
        player = p.get();
        engine.addObject(std::move(p));

        // Spawner
        spawner = new Spawner(engine, player);

        score = 0;
        survivalTime = 0.0f;
        state = GameState::PLAYING;
    }

    void Game::goToMenu() {
        engine.clearObjects();

        engine.addObject(std::make_unique<Starfield>());

        auto menu = std::make_unique<MenuScene>(this);
        menuScene = menu.get();
        engine.addObject(std::move(menu));

        state = GameState::MENU;
    }

    void Game::run() {
        engine.setUpdateCallback([this](float dt) { onUpdate(dt); });
        engine.run();
    }

    void Game::onUpdate(float dt) {

        if (state == GameState::MENU) {
            if (menuScene) {
                menuScene->update(dt);
                menuScene->handleInput(engine.getInput());
            }
            return;
        }

        if (state == GameState::GAMEOVER) {
            if (gameOverScene) {
                gameOverScene->handleInput(engine.getInput());
            }
            return;
        }

        survivalTime += dt;
        score = (int)(survivalTime * GameConfig::SCORE_PER_SECOND);

        spawner->update(dt);
        checkCollisions();
    }

    void Game::checkCollisions()
    {
        //  HOMING
        for (auto* b : spawner->getHomingBullets()) {
            if (b->isDead() || b->isOffBoard()) continue;
            if (player->hitboxCollidesCircle(b->getCenter(), GameConfig::BULLET_RADIUS)) {
                if (player->takeDamage()) {
                    b->kill();

                    if (player->getLives() <= 0) {
                        state = GameState::GAMEOVER;
                        auto goScene = std::make_unique<GameOverScene>(this);
                        gameOverScene = goScene.get();
                        engine.addObject(std::move(goScene));
                        return;
                    }
                }
            }
        }

        //  POCISKI TRACKER
        for (auto* b : spawner->getTrackerBullets()) {
            if (b->isDead() || b->isOffBoard()) continue;
            if (player->hitboxCollidesCircle(b->getCenter(), GameConfig::BULLET_RADIUS)) {
                if (player->takeDamage()) {
                    b->kill();

                    if (player->getLives() <= 0) {
                        state = GameState::GAMEOVER;
                        auto goScene = std::make_unique<GameOverScene>(this);
                        gameOverScene = goScene.get();
                        engine.addObject(std::move(goScene));
                        return;
                    }
                }
            }
        }

        //  BOMBY
        for (auto* b : spawner->getBombs()) {
            if (b->isDead()) continue;

            if (!b->hasExploded()) {

                if (player->hitboxCollidesCircle(b->getCenter(), GameConfig::BOMB_RADIUS)) {
                    b->explodeNow();

                    if (player->takeDamage()) {
                        if (player->getLives() <= 0) {
                            state = GameState::GAMEOVER;
                            auto goScene = std::make_unique<GameOverScene>(this);
                            gameOverScene = goScene.get();
                            engine.addObject(std::move(goScene));
                            return;
                        }
                    }
                }
            } else {

                float radius = GameConfig::BOMB_EXPLODE_RADIUS * b->getExplosionProgress();
                if (player->hitboxCollidesCircle(b->getCenter(), radius)) {
                    if (player->takeDamage()) {
                        if (player->getLives() <= 0) {
                            state = GameState::GAMEOVER;
                            auto goScene = std::make_unique<GameOverScene>(this);
                            gameOverScene = goScene.get();
                            engine.addObject(std::move(goScene));
                            return;
                        }
                    }
                }
            }
        }
    }

} // namespace game
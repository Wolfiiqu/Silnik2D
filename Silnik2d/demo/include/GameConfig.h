#pragma once
/**
 * @file GameConfig.hpp
 * @brief Stałe konfiguracyjne gry.
 */
#pragma once

namespace game {

    struct GameConfig {
        // Okno
        static constexpr int WINDOW_W = 1000;
        static constexpr int WINDOW_H = 700;

        // Plansza: 80% okna
        static constexpr float BOARD_SCALE = 0.8f;
        static constexpr float BOARD_W = WINDOW_W * BOARD_SCALE;
        static constexpr float BOARD_H = WINDOW_H * BOARD_SCALE;
        static constexpr float BOARD_X = (WINDOW_W - BOARD_W) / 2;
        static constexpr float BOARD_Y = (WINDOW_H - BOARD_H) / 2;

        // Gracz
        static constexpr float PLAYER_SIZE = 40;
        static constexpr float PLAYER_SPEED = 280;

        // Pociski
        static constexpr float BULLET_SPEED = 180;
        static constexpr float BULLET_RADIUS = 8;
        static constexpr float BULLET_LIFETIME = 8.0f;

        // Bomba
        static constexpr float BOMB_FALL_SPEED = 120;
        static constexpr float BOMB_RADIUS = 20;
        static constexpr float BOMB_FUSE = 2.0f;
        static constexpr float BOMB_EXPLODE_RADIUS = 60;
        static constexpr float BOMB_EXPLODE_TIME = 0.5f;

        // Spawn
        static constexpr float HOMING_INTERVAL = 1.8f;
        static constexpr float TRACKER_INTERVAL = 2.8f;
        static constexpr float BOMB_INTERVAL = 3.5f;

        // Kolizje
        static constexpr float COLLISION_MARGIN = 4.0f;

        // Życie i punktacja
        static constexpr int PLAYER_LIVES = 3;
        static constexpr float INVINCIBILITY_TIME = 2.0f;
        static constexpr int SCORE_PER_SECOND = 10;

        // === BALANS TRUDNOŚCI ===
        static constexpr float MAX_SPAWN_MULT = 2.3f;
        static constexpr float MAX_HOMING_SPEED_MULT = 1.4f;
        static constexpr float MAX_TRACKER_SPEED_MULT = 1.3f;
        static constexpr float MAX_BOMB_SPEED_MULT = 1.5f;   
    };

}
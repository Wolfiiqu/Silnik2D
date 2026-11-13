#pragma once
/**
 * @file Board.hpp
 * @brief Plansza gry — granice, sprawdzanie kolizji.
 */

#include "..\demo\include\GameConfig.h"
#include "Renderer.h"
#include "..\include\Renderer.h"

namespace game {

    class Board {
    public:
        /// @brief Czy punkt jest wewnątrz planszy.
        static bool contains(float x, float y);

        /// @brief Ogranicza pozycję (x,y) rozmiaru (w,h) do planszy.
        static void clamp(float& x, float& y, float w, float h);

        /// @brief Rysuje ramkę planszy.
        static void draw(engine2d::Renderer& r);
    };

} // namespace game


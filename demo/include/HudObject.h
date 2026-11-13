#pragma once
/**
 * @file HudObject.h
 * @brief HUD — życia i punktacja jako DrawableObject.
 */

#include "../include/DrawableObject.h"
#include <SFML/Graphics.hpp>
#include <string>
namespace game {

    class Game;

    class HudObject {
        const Game* game;
        sf::Font font;
        bool fontLoaded = false;

    public:
        explicit HudObject(const Game* g);
        void draw(sf::RenderWindow& window);
    };

}

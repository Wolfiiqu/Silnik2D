#pragma once
#include "../include/DrawableObject.h"
#include "../include/Leaderboard.h"
#include "../include/InputManager.h"
#include <SFML/Graphics.hpp>

namespace game {
    class Game;

    class GameOverScene : public engine2d::DrawableObject {
    private:
        Game* game;
        sf::Font font;
        bool fontLoaded = false;

        Leaderboard leaderboard;

        sf::FloatRect restartBtnBounds;
        sf::FloatRect menuBtnBounds;

        void drawButton(sf::RenderWindow& window, sf::FloatRect bounds, const std::string& text, bool hovered) const;

    public:
        explicit GameOverScene(Game* g);
        void handleInput(const engine2d::InputManager& input);
        void draw(engine2d::Renderer& r) override;
        void drawUI(sf::RenderWindow& window);
    };
}
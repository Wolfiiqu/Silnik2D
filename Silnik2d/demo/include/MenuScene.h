#pragma once
#include "../include/DrawableObject.h"
#include "../include/InputManager.h"
#include "../include/Point2D.h"
#include "../include/LineSegment.h"
#include "../include/Elipsa.h"
#include "../include/Triangle.h"
#include "../include/Rectangle.h"
#include <SFML/Graphics.hpp>

namespace game {
    class Game; // forward declaration

    class MenuScene : public engine2d::DrawableObject {
    private:
        Game* game;
        sf::Font font;
        bool fontLoaded = false;

        engine2d::Ellipse bgEllipse{80, 40};
        engine2d::Triangle bgTriangle{{-30,30}, {30,30}, {0,-30}};
        engine2d::Rectangle bgRect{60, 60};

        float elapsedTime = 0.0f; // ← ZMIENIONE Z time

        sf::FloatRect startBtnBounds;
        sf::FloatRect exitBtnBounds;

        // Dodane const
        void drawButton(sf::RenderWindow& window, sf::FloatRect bounds, const std::string& text, bool hovered) const;

    public:
        explicit MenuScene(Game* g);

        void update(float dt);
        void handleInput(const engine2d::InputManager& input); // ← DODANE CONST
        void draw(engine2d::Renderer& r) override;
        void drawUI(sf::RenderWindow& window);
    };
}
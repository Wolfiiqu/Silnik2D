#include "../include/MenuScene.h"
#include "../include/Game.h"
#include "../include/GameConfig.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace game {
using namespace engine2d;

MenuScene::MenuScene(Game* g) : game(g) {
    fontLoaded = font.loadFromFile("assets/font.ttf");

    // Ustawiamy tylko kolory. Pozycje ustawimy dynamicznie w update().
    bgEllipse.setColor(Color(100, 100, 255));
    bgTriangle.setColor(Color(255, 100, 100));
    bgRect.setColor(Color(100, 255, 100));
}

    void MenuScene::update(float dt) {
    elapsedTime += dt;

    // Owal pulsuje (zmieniamy jego promienie)
    bgEllipse.resetTransform();
    float scale = 1.0f + 0.2f * std::sin(elapsedTime * 5.0f);
    bgEllipse.setRadii(80.0f * scale, 40.0f * scale);
    bgEllipse.translate(150, 150);

    // Trójkąt obraca się w miejscu
    bgTriangle.resetTransform();
    bgTriangle.rotate(elapsedTime * 30.0f);
    bgTriangle.translate(GameConfig::WINDOW_W - 200, 150);

    // Prostokąt: kręci się i wyraźnie LATA po ekranie (translate)
    bgRect.resetTransform();
    bgRect.translate(-30, -30);
    bgRect.rotate(elapsedTime * 45.0f);

    // Ruch po ósemce (Lissajous) na dole ekranu
    float moveX = GameConfig::WINDOW_W / 2 + 300.0f * std::sin(elapsedTime * 1.5f);
    float moveY = GameConfig::WINDOW_H - 150 + 80.0f * std::cos(elapsedTime * 3.0f);

    bgRect.translate(moveX, moveY);
}

void MenuScene::handleInput(const InputManager& input) {
    if (input.isMouseJustPressed(sf::Mouse::Left)) {
        Point2D m = input.getMousePosition();

        if (startBtnBounds.contains(m.x, m.y)) {
            game->startGame();
        }
        if (exitBtnBounds.contains(m.x, m.y)) {
            std::exit(0);
        }
    }
}

void MenuScene::draw(Renderer& r) {

    bgEllipse.draw(r);
    bgTriangle.draw(r);
    bgRect.draw(r);
}

void MenuScene::drawUI(sf::RenderWindow& window) {
    // Tytuł
    if (fontLoaded) {
        sf::Text title("SILNIK 2D", font, 80);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        sf::FloatRect b = title.getLocalBounds();
        title.setPosition(GameConfig::WINDOW_W/2 - b.width/2, 100);
        window.draw(title);
    }

    // Współrzędne przycisków
    startBtnBounds = sf::FloatRect(GameConfig::WINDOW_W/2 - 100, 350, 200, 60);
    exitBtnBounds = sf::FloatRect(GameConfig::WINDOW_W/2 - 100, 450, 200, 60);

    // Sprawdzenie hover
    auto mouse = sf::Mouse::getPosition(window);
    bool hoverStart = startBtnBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
    bool hoverExit = exitBtnBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

    // Rysowanie
    drawButton(window, startBtnBounds, "GRAJ", hoverStart);
    drawButton(window, exitBtnBounds, "WYJDZ", hoverExit);
}

void MenuScene::drawButton(sf::RenderWindow& window, sf::FloatRect bounds, const std::string& text, bool hovered) const {
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(hovered ? sf::Color(50, 50, 80) : sf::Color(30, 30, 50));
    rect.setOutlineThickness(2);
    rect.setOutlineColor(hovered ? sf::Color::White : sf::Color(150, 150, 150));
    window.draw(rect);

    if (fontLoaded) {
        sf::Text t(text, font, 30);
        sf::FloatRect b = t.getLocalBounds();
        t.setPosition(bounds.left + bounds.width/2 - b.width/2, bounds.top + bounds.height/2 - b.height/2 - 5);
        t.setFillColor(hovered ? sf::Color::White : sf::Color(200, 200, 200));
        window.draw(t);
    }
}

} // namespace game
#include "../include/GameOverScene.h"
#include "../include/Game.h"
#include "../include/GameConfig.h"

namespace game {
using namespace engine2d;

GameOverScene::GameOverScene(Game* g) : game(g) {
    fontLoaded = font.loadFromFile("assets/font.ttf");
    if (game) {
        leaderboard.addScore(game->getScore());
    }
}

void GameOverScene::handleInput(const InputManager& input) {
    if (input.isMouseJustPressed(sf::Mouse::Left)) {
        Point2D m = input.getMousePosition();
        
        if (restartBtnBounds.contains(m.x, m.y)) {
            game->startGame();
        }
        if (menuBtnBounds.contains(m.x, m.y)) {
            game->goToMenu();
        }
    }
}

void GameOverScene::draw(Renderer& r) {

    std::vector<Point2D> rect = {
        {0, 0}, {(float)GameConfig::WINDOW_W, 0}, 
        {(float)GameConfig::WINDOW_W, (float)GameConfig::WINDOW_H}, {0, (float)GameConfig::WINDOW_H}
    };
    r.scanlineFill(rect, Color(0, 0, 0, 180));
}

void GameOverScene::drawUI(sf::RenderWindow& window) {
    if (!fontLoaded) return;

    // Tytuł
    sf::Text title("KONIEC GRY", font, 70);
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    sf::FloatRect b = title.getLocalBounds();
    title.setPosition(GameConfig::WINDOW_W/2 - b.width/2, 100);
    window.draw(title);

    // Twój wynik
    sf::Text scoreText("Twoj wynik: " + std::to_string(game->getScore()), font, 40);
    scoreText.setFillColor(sf::Color::White);
    sf::FloatRect sb = scoreText.getLocalBounds();
    scoreText.setPosition(GameConfig::WINDOW_W/2 - sb.width/2, 200);
    window.draw(scoreText);

    restartBtnBounds = sf::FloatRect(GameConfig::WINDOW_W/2 - 320, 400, 280, 60);
    menuBtnBounds = sf::FloatRect(GameConfig::WINDOW_W/2 - 320, 480, 280, 60);

    auto mouse = sf::Mouse::getPosition(window);
    bool hoverRestart = restartBtnBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
    bool hoverMenu = menuBtnBounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

    drawButton(window, restartBtnBounds, "ZAGRAJ PONOWNIE", hoverRestart);
    drawButton(window, menuBtnBounds, "POWROT DO MENU", hoverMenu);


    sf::Text lbTitle("NAJLEPSZE WYNIKI:", font, 24);
    lbTitle.setFillColor(sf::Color(255, 200, 0));

    lbTitle.setPosition(GameConfig::WINDOW_W / 2 + 50, 400);
    window.draw(lbTitle);

    const auto& scores = leaderboard.getScores();
    for (size_t i = 0; i < scores.size(); ++i) {
        sf::Text scoreEntry(std::to_string(i + 1) + ". " + std::to_string(scores[i]), font, 24);
        scoreEntry.setFillColor(sf::Color::White);
        scoreEntry.setPosition(GameConfig::WINDOW_W / 2 + 50, 440 + i * 30);
        window.draw(scoreEntry);
    }
}

void GameOverScene::drawButton(sf::RenderWindow& window, sf::FloatRect bounds, const std::string& text, bool hovered) const {
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setFillColor(hovered ? sf::Color(80, 30, 30) : sf::Color(40, 20, 20));
    rect.setOutlineThickness(2);
    rect.setOutlineColor(hovered ? sf::Color::Red : sf::Color(150, 50, 50));
    window.draw(rect);

    if (fontLoaded) {
        sf::Text t(text, font, 20);
        sf::FloatRect b = t.getLocalBounds();
        t.setPosition(bounds.left + bounds.width/2 - b.width/2, bounds.top + bounds.height/2 - b.height/2 - 5);
        t.setFillColor(hovered ? sf::Color::White : sf::Color(200, 200, 200));
        window.draw(t);
    }
}

} // namespace game
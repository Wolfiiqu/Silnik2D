#include "../demo/include/HudObject.h"
#include "../demo/include/Game.h"
#include "../demo/include/GameConfig.h"
#include <string>

namespace game {

HudObject::HudObject(const Game* g) : game(g) {
    // Ładuj czcionkę — musi być w assets/font.ttf
    fontLoaded = font.loadFromFile("assets/font.ttf");
}

void HudObject::draw(sf::RenderWindow& window) {
    if (!game) return;

    // === ŻYCIA ===
    if (fontLoaded) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color(0, 255, 100));
        text.setPosition(GameConfig::BOARD_X, GameConfig::BOARD_Y - 40);
        text.setString("Zycia: " + std::to_string(game->getPlayerLives()));
        window.draw(text);

        // === PUNKTACJA ===
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color(255, 200, 0));
        scoreText.setPosition(GameConfig::BOARD_X + GameConfig::BOARD_W - 200,
                              GameConfig::BOARD_Y - 40);
        scoreText.setString("Punkty: " + std::to_string(game->getScore()));
        window.draw(scoreText);
    }

    // === GAME OVER ===
    if (game->isGameOver() && fontLoaded) {
        sf::Text goText;
        goText.setFont(font);
        goText.setCharacterSize(48);
        goText.setFillColor(sf::Color(255, 50, 50));
        goText.setString("GAME OVER");
        // Wyśrodkuj
        sf::FloatRect bounds = goText.getLocalBounds();
        goText.setPosition(
            GameConfig::BOARD_X + GameConfig::BOARD_W / 2 - bounds.width / 2,
            GameConfig::BOARD_Y + GameConfig::BOARD_H / 2 - bounds.height / 2 - 30
        );
        window.draw(goText);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setCharacterSize(24);
        restartText.setFillColor(sf::Color(255, 255, 255));
        restartText.setString("Nacisnij R aby zrestartowac");
        sf::FloatRect rb = restartText.getLocalBounds();
        restartText.setPosition(
            GameConfig::BOARD_X + GameConfig::BOARD_W / 2 - rb.width / 2,
            GameConfig::BOARD_Y + GameConfig::BOARD_H / 2 + 30
        );
        window.draw(restartText);
    }
}

}
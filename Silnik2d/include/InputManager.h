

#ifndef SILNIK2D_INPUTMANAGER_H
#define SILNIK2D_INPUTMANAGER_H

#pragma once
/**
 * @file InputManager.hpp
 * @brief Obsługa klawiatury i myszy (lab01).
 * @author Osoba C
 * @date 2026
 */

#include <SFML/Window.hpp>
#include <set>
#include "Point2D.h"

namespace engine2d {

    /**
     * @brief Menedżer wejścia — zbiera stan klawiatury i myszy.
     */
    class InputManager {
    private:
        std::set<sf::Keyboard::Key> pressed;      ///< Wciśnięte klawisze.
        std::set<sf::Keyboard::Key> justPressed;  ///< Klawisze wciśnięte w tej klatce.
        std::set<sf::Mouse::Button> mousePressed; ///< Wciśnięte przyciski myszy.
        Point2D mousePos;                         ///< Pozycja myszy.

    public:
        /**
         * @brief Przetwarza zdarzenie SFML.
         * @param e Zdarzenie.
         */
        void handleEvent(const sf::Event& e);

        /// @brief Wywoływane na końcu klatki — czyści justPressed.
        void endFrame();

        /**
         * @brief Czy klawisz jest aktualnie wciśnięty.
         * @param k Klawisz.
         */
        bool isKeyDown(sf::Keyboard::Key k) const;

        /**
         * @brief Czy klawisz został wciśnięty w tej klatce.
         * @param k Klawisz.
         */
        bool isKeyJustPressed(sf::Keyboard::Key k) const;

        /// @brief Zwraca pozycję myszy.
        Point2D getMousePosition() const { return mousePos; }

        /**
         * @brief Czy przycisk myszy jest wciśnięty.
         * @param b Przycisk.
         */
        bool isMouseDown(sf::Mouse::Button b) const;
    };

} // namespace engine2d
#endif //SILNIK2D_INPUTMANAGER_H
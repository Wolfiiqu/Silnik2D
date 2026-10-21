
#pragma once
/**
 * @file Engine.hpp
 * @brief Główna klasa silnika — pętla gry (lab01).
 * @author Osoba C
 * @date 2026
 */

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Renderer.h"
#include "InputManager.h"
#include "GameObject.h"

namespace engine2d {

    /**
     * @brief Główna klasa silnika: okno, pętla, input, obiekty.
     *
     * Wykorzystuje double buffering (SFML domyślnie).
     */
    class Engine {
    private:
        sf::RenderWindow window;                          ///< Okno SFML.
        Renderer renderer;                                ///< Renderer.
        InputManager input;                               ///< Menedżer inputu.
        std::vector<std::unique_ptr<GameObject>> objects; ///< Obiekty gry.
        sf::Clock clock;                                  ///< Zegar do dt.

    public:
        /**
         * @brief Konstruktor — tworzy okno.
         * @param width Szerokość okna.
         * @param height Wysokość okna.
         * @param title Tytuł okna.
         */
        Engine(int width, int height, const std::string& title);

        /// @brief Uruchamia główną pętlę gry (blokuje do zamknięcia okna).
        void run();

        /**
         * @brief Dodaje obiekt do sceny (przejmuje własność).
         * @param obj Unikalny wskaźnik do obiektu.
         */
        void addObject(std::unique_ptr<GameObject> obj);

        /// @brief Zwraca renderer.
        Renderer& getRenderer() { return renderer; }
        /// @brief Zwraca input.
        InputManager& getInput() { return input; }
        /// @brief Zwraca okno.
        sf::RenderWindow& getWindow() { return window; }
    };

} // namespace engine2d


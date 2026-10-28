
#pragma once
/**
 * @file GameObject.hpp
 * @brief Bazowa klasa wszystkich obiektów gry (lab04).
 * @author Osoba B
 * @date 2026
 */

namespace engine2d {

    /**
     * @brief Bazowa klasa hierarchii obiektów gry.
     *
     * Posiada wyłącznie wirtualny destruktor. Klasy pochodne
     * (DrawableObject, TransformableObject, UpdatableObject) dziedziczą
     * po niej wirtualnie, aby uniknąć problemu diamentu (lab04 str.6).
     */
    class GameObject {
    public:
        virtual ~GameObject() = default;
    };

}


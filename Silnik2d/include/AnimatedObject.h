#pragma once
/**
 * @file AnimatedObject.hpp
 * @brief Interfejs obiektów animowanych (lab05).
 * @author Osoba C
 * @date 2026
 */

namespace engine2d {

    /**
     * @brief Interfejs obiektów animowanych klatkowo.
     */
    class AnimatedObject {
    public:
        virtual ~AnimatedObject() = default;

        /**
         * @brief Aktualizuje animację.
         * @param dt Delta czasu w sekundach.
         */
        virtual void animate(float dt) = 0;
    };

}
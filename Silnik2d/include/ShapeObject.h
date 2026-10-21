


#pragma once
/**
 * @file ShapeObject.hpp
 * @brief Bazowa klasa figur geometrycznych (lab04).
 * @author Osoba B
 * @date 2026
 */

#include "DrawableObject.h"
#include "TransformableObject.h"
#include "Color.h"

namespace engine2d {

    /**
     * @brief Bazowa klasa dla wszystkich figur geometrycznych.
     *
     * Dziedziczy wirtualnie po DrawableObject i TransformableObject
     * (lab04 str.6 — unikanie problemu diamentu).
     */
    class ShapeObject : virtual public DrawableObject,
                        virtual public TransformableObject {
    protected:
        Color color;         ///< Kolor figury.
        bool filled = false; ///< Czy figura jest wypełniona.

    public:
        virtual ~ShapeObject() = default;

        /// @brief Ustawia kolor figury.
        void setColor(Color c) { color = c; }
        /// @brief Zwraca kolor figury.
        Color getColor() const { return color; }
        /// @brief Ustawia tryb wypełnienia.
        void setFilled(bool f) { filled = f; }
        /// @brief Czy figura jest wypełniona.
        bool isFilled() const { return filled; }
    };

} // namespace engine2d



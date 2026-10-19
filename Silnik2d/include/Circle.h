

#ifndef SILNIK2D_CIRCLE_H
#define SILNIK2D_CIRCLE_H

#pragma once
/**
 * @file Circle.hpp
 * @brief Okrąg (lab03).
 * @author Osoba B
 */
#include "ShapeObject.h"

namespace engine2d {

    /**
     * @brief Okrąg o zadanym promieniu.
     */
    class Circle : public ShapeObject {
    private:
        float radius;
    public:
        /**
         * @brief Konstruktor.
         * @param radius Promień.
         */
        Circle(float radius) : radius(radius) {}

        /// @brief Rysuje okrąg (8-krotna symetria z lab03).
        void draw(Renderer& r) override;
    };

} // namespace engine2d


#endif //SILNIK2D_CIRCLE_H
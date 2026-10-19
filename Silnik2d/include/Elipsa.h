#ifndef SILNIK2D_ELIPSA_H
#define SILNIK2D_ELIPSA_H


#pragma once
/**
 * @file Ellipse.hpp
 * @brief Elipsa (lab03).
 * @author Osoba B
 */
#include "ShapeObject.h"

namespace engine2d {

    /**
     * @brief Elipsa o zadanych promieniach rx, ry.
     */
    class Ellipse : public ShapeObject {
    private:
        float rx, ry;
    public:
        /**
         * @brief Konstruktor.
         * @param rx Promień X.
         * @param ry Promień Y.
         */
        Ellipse(float rx, float ry) : rx(rx), ry(ry) {}

        /// @brief Rysuje elipsę (4-krotna symetria z lab03).
        void draw(Renderer& r) override;
    };

} // namespace engine2d

#endif //SILNIK2D_ELIPSA_H
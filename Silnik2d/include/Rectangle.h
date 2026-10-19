
#ifndef SILNIK2D_RECTANGLE_H
#define SILNIK2D_RECTANGLE_H

#pragma once
/**
 * @file Rectangle.hpp
 * @brief Prostokąt (lab03).
 * @author Osoba B
 */
#include "ShapeObject.h"

namespace engine2d {

    /**
     * @brief Prostokąt o zadanej szerokości i wysokości.
     */
    class Rectangle : public ShapeObject {
    private:
        float w, h;
    public:
        /**
         * @brief Konstruktor.
         * @param w Szerokość.
         * @param h Wysokość.
         */
        Rectangle(float w, float h) : w(w), h(h) {}

        /// @brief Rysuje prostokąt (przez 4 odcinki lub scanline fill).
        void draw(Renderer& r) override;
    };

} // namespace engine2d
#endif //SILNIK2D_RECTANGLE_H
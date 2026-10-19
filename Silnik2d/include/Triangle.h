

#ifndef SILNIK2D_TRIANGLE_H
#define SILNIK2D_TRIANGLE_H

#pragma once
/**
 * @file Triangle.hpp
 * @brief Trójkąt (lab03).
 * @author Osoba B
 */
#include "Shape.h"

namespace engine2d {

    /**
     * @brief Trójkąt zdefiniowany przez 3 wierzchołki.
     */
    class Triangle : public ShapeObject {
    private:
        Point2D a, b, c;
    public:
        /**
         * @brief Konstruktor.
         * @param a Wierzchołek 1.
         * @param b Wierzchołek 2.
         * @param c Wierzchołek 3.
         */
        Triangle(Point2D a, Point2D b, Point2D c) : a(a), b(b), c(c) {}

        /// @brief Rysuje trójkąt (kontur lub scanline fill).
        void draw(Renderer& r) override;
    };

} // namespace engine2d

#endif //SILNIK2D_TRIANGLE_H
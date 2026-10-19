

#ifndef SILNIK2D_POLYGON_H
#define SILNIK2D_POLYGON_H

#pragma once
/**
 * @file Polygon.hpp
 * @brief Wielokąt (lab03).
 * @author Osoba B
 */
#include "Shape.h"
#include <vector>

namespace engine2d {

    /**
     * @brief Wielokąt zdefiniowany przez listę wierzchołków.
     */
    class Polygon : public ShapeObject {
    private:
        std::vector<Point2D> points;
    public:
        /**
         * @brief Konstruktor.
         * @param pts Wierzchołki.
         */
        Polygon(const std::vector<Point2D>& pts) : points(pts) {}

        /// @brief Rysuje wielokąt (kontur lub scanline fill).
        void draw(Renderer& r) override;
    };

} // namespace engine2d


#endif //SILNIK2D_POLYGON_H
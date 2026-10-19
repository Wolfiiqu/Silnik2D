
#ifndef SILNIK2D_LINE_H
#define SILNIK2D_LINE_H


#pragma once
/**
 * @file Line.h
 * @brief Odcinek z metodami przekształceń (lab02, lab04).
 * @author Osoba A
 * @date 2026
 */

#include "Point2D.h"

namespace engine2d {

    class Renderer;

    /**
     * @brief Odcinek 2D zbudowany z dwóch punktów.
     *
     * Zgodnie z lab04 (str. 2), przekształcenia odcinka realizujemy
     * poprzez przekształcenie wyłącznie jego końców.
     */
    class LineSegment {
    public:
        Point2D p1; ///< Początek odcinka.
        Point2D p2; ///< Koniec odcinka.

        /**
         * @brief Konstruktor odcinka.
         * @param a Początek.
         * @param b Koniec.
         */
        LineSegment(Point2D a = {}, Point2D b = {}) : p1(a), p2(b) {}

        // ===== lab02: odczyt/zapis końców =====

        /// @brief Zwraca początek odcinka.
        Point2D getP1() const { return p1; }
        /// @brief Zwraca koniec odcinka.
        Point2D getP2() const { return p2; }
        /// @brief Ustawia początek odcinka.
        void setP1(Point2D p) { p1 = p; }
        /// @brief Ustawia koniec odcinka.
        void setP2(Point2D p) { p2 = p; }

        // ===== lab04: przekształcenia =====

        /// @brief Translacja obu końców.
        void translate(float tx, float ty);
        /// @brief Rotacja obu końców względem (0,0).
        void rotate(float deg);
        /// @brief Rotacja obu końców względem punktu pivot.
        void rotateAround(const Point2D& pivot, float deg);
        /// @brief Skalowanie obu końców względem (0,0).
        void scale(float kx, float ky);
        /// @brief Skalowanie obu końców względem punktu pivot.
        void scaleAround(const Point2D& pivot, float kx, float ky);

        // ===== lab02: rysowanie =====

        /**
         * @brief Rysuje odcinek za pomocą Renderera.
         * @param r Referencja do Renderera.
         */
        void draw(Renderer& r) const;
    };

}
#endif //SILNIK2D_LINE_H
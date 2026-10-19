
#ifndef SILNIK2D_TRANSFORM2D_H
#define SILNIK2D_TRANSFORM2D_H

#pragma once
/**
 * @file Transform2D.hpp
 * @brief Macierz transformacji 3x3 dla przestrzeni 2D (fundament lab04).
 * @author Osoba A
 * @date 2026
 */

#include "Point2D.h"

namespace engine2d {

/**
 * @brief Macierz transformacji 3x3.
 *
 * Konwencja: punkt jest wektorem kolumnowym [x, y, 1]^T.
 * Złożenie T * R * S oznacza: najpierw skala, potem rotacja, potem translacja.
 * Mutatory mnożą z lewej: this = M * this.
 */
class Transform2D {
private:
    float m[3][3]; ///< Wewnętrzna macierz 3x3.

public:
    /// @brief Konstruktor — macierz jednostkowa.
    Transform2D();

    /// @brief Reset do macierzy jednostkowej.
    void reset();

    /**
     * @brief Tworzy macierz translacji.
     * @param tx Przesunięcie X.
     * @param ty Przesunięcie Y.
     * @return Macierz translacji.
     */
    static Transform2D translation(float tx, float ty);

    /**
     * @brief Tworzy macierz rotacji.
     * @param deg Kąt w stopniach (CCW wizualnie, kompensacja Y-down).
     * @return Macierz rotacji.
     */
    static Transform2D rotation(float deg);

    /**
     * @brief Tworzy macierz skalowania.
     * @param kx Współczynnik skali X.
     * @param ky Współczynnik skali Y.
     * @return Macierz skalowania.
     */
    static Transform2D scaling(float kx, float ky);

    /**
     * @brief Mnożenie dwóch macierzy transformacji.
     * @param o Prawa macierz.
     * @return Iloczyn (this * o).
     */
    Transform2D operator*(const Transform2D& o) const;

    /**
     * @brief Nakłada transformację na punkt.
     * @param p Punkt wejściowy.
     * @return Punkt po transformacji.
     */
    Point2D apply(const Point2D& p) const;

    /**
     * @brief Nakłada transformację na wektor (bez translacji).
     * @param v Wektor wejściowy.
     * @return Wektor po transformacji.
     */
    Point2D applyVector(const Point2D& v) const;

    /**
     * @brief Modyfikuje punkt in-place.
     * @param p Punkt do zmodyfikowania.
     */
    void applyInPlace(Point2D& p) const { p = apply(p); }

    /// @brief Translacja z lewej: this = T * this.
    void translate(float tx, float ty);
    /// @brief Rotacja z lewej: this = R * this.
    void rotate(float deg);
    /// @brief Skalowanie z lewej: this = S * this.
    void scale(float kx, float ky);

    /**
     * @brief Odwrotność macierzy afinicznej.
     * @return Macierz odwrotna lub identity dla macierzy osobliwej.
     */
    Transform2D inverse() const;

    /// @brief Surowe dane macierzy (dla integracji z SFML).
    const float (*getRaw() const)[3] { return m; }
};

} // namespace engine2d

#endif //SILNIK2D_TRANSFORM2D_H
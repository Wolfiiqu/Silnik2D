

#ifndef SILNIK2D_POINT2D_H
#define SILNIK2D_POINT2D_H

#pragma once
/**
 * @file Point2D.hpp
 * @brief Punkt 2D z metodami przekształceń (lab02, lab04).
 * @author Osoba A
 * @date 2026
 */

namespace engine2d {

class Renderer; // forward declaration

/**
 * @brief Punkt w przestrzeni 2D.
 *
 * Układ współrzędnych: Y-down (ekranowy), zgodny z SFML.
 * Rotacja jest kompensowana tak, aby wizualnie na ekranie obrót
 * dodatni wyglądał jak przeciwnie do wskazówek zegara (CCW).
 *
 * Zawiera metody przekształceń geometrycznych wymagane przez lab04:
 * translację, rotację i jednokładność (względem początku i dowolnego punktu).
 */
class Point2D {
public:
    float x; ///< Współrzędna X.
    float y; ///< Współrzędna Y.

    /**
     * @brief Konstruktor punktu.
     * @param x Współrzędna X (domyślnie 0).
     * @param y Współrzędna Y (domyślnie 0).
     */
    Point2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // ===== lab02: odczyt/zapis współrzędnych =====

    /// @brief Zwraca współrzędną X.
    float getX() const { return x; }
    /// @brief Zwraca współrzędną Y.
    float getY() const { return y; }
    /// @brief Ustawia współrzędną X.
    void setX(float v) { x = v; }
    /// @brief Ustawia współrzędną Y.
    void setY(float v) { y = v; }

    // ===== lab04: przekształcenia względem (0,0) =====

    /**
     * @brief Translacja punktu o wektor (tx, ty).
     * @param tx Przesunięcie w osi X.
     * @param ty Przesunięcie w osi Y.
     */
    void translate(float tx, float ty);

    /**
     * @brief Rotacja względem początku układu o kąt w stopniach (CCW).
     * @param deg Kąt w stopniach.
     */
    void rotate(float deg);

    /**
     * @brief Skalowanie względem początku układu.
     * @param kx Współczynnik skali w osi X.
     * @param ky Współczynnik skali w osi Y.
     */
    void scale(float kx, float ky);

    // ===== lab04: przekształcenia względem dowolnego punktu =====

    /**
     * @brief Rotacja względem punktu pivot o kąt w stopniach.
     * @param pivot Punkt, wokół którego obracamy.
     * @param deg Kąt w stopniach.
     */
    void rotateAround(const Point2D& pivot, float deg);

    /**
     * @brief Skalowanie względem punktu pivot.
     * @param pivot Punkt, względem którego skalujemy.
     * @param kx Współczynnik skali w osi X.
     * @param ky Współczynnik skali w osi Y.
     */
    void scaleAround(const Point2D& pivot, float kx, float ky);

    // ===== wersje funkcyjne (zwracają nowy punkt) =====

    /// @brief Zwraca nowy punkt po translacji.
    Point2D translated(float tx, float ty) const;
    /// @brief Zwraca nowy punkt po rotacji.
    Point2D rotated(float deg) const;
    /// @brief Zwraca nowy punkt po skalowaniu.
    Point2D scaled(float kx, float ky) const;

    // ===== lab02: rysowanie =====

    /**
     * @brief Rysuje punkt (pojedynczy piksel) za pomocą Renderera.
     * @param r Referencja do Renderera.
     */
    void draw(Renderer& r) const;

    // ===== operatory =====

    /// @brief Dodawanie punktów (wektorowo).
    Point2D operator+(const Point2D& o) const { return {x + o.x, y + o.y}; }
    /// @brief Odejmowanie punktów (wektorowo).
    Point2D operator-(const Point2D& o) const { return {x - o.x, y - o.y}; }
    /// @brief Mnożenie przez skalar.
    Point2D operator*(float s) const { return {x * s, y * s}; }

    /**
     * @brief Odległość euklidesowa do innego punktu.
     * @param o Drugi punkt.
     * @return Odległość w pikselach.
     */
    float distance(const Point2D& o) const;
};

} // namespace engine2d

#endif //SILNIK2D_POINT2D_H

#ifndef SILNIK2D_RENDERER_H
#define SILNIK2D_RENDERER_H


#pragma once
/**
 * @file Renderer.hpp
 * @brief Renderer 2D z algorytmami rysowania (lab02, lab03).
 * @author Osoba B
 * @date 2026
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include "Point2D.h"
#include "Color.h"

namespace engine2d {

/**
 * @brief Renderer rysujący na buforze SFML.
 *
 * Wszystkie prymitywy są rysowane własnymi algorytmami
 * (algorytm przyrostowy z lab02, okrąg/elipsa z symetrią z lab03,
 * wypełnianie flood/boundary/scanline z lab03) — NIE używamy
 * sf::CircleShape / sf::RectangleShape.
 */
class Renderer {
private:
    sf::RenderWindow& window;  ///< Referencja do okna.
    sf::Image buffer;          ///< Bufor obrazu (do rysowania pikseli).
    sf::Texture texture;       ///< Tekstura do wyświetlania bufora.
    sf::Sprite screenSprite;   ///< Sprite wyświetlający bufor.

public:
    /**
     * @brief Konstruktor.
     * @param w Referencja do okna SFML.
     */
    explicit Renderer(sf::RenderWindow& w);

    /// @brief Czyści bufor kolorem.
    void clear(Color c = Color::Black());
    /// @brief Wyświetla bufor na ekranie (double buffering SFML).
    void display();

    // ===== lab02 =====

    /**
     * @brief Rysuje pojedynczy piksel.
     * @param x Współrzędna X.
     * @param y Współrzędna Y.
     * @param c Kolor (domyślnie biały).
     */
    void drawPixel(int x, int y, Color c = Color::White());

    /**
     * @brief Rysuje odcinek algorytmem przyrostowym (lab02).
     * @param a Początek.
     * @param b Koniec.
     * @param c Kolor.
     */
    void drawLine(Point2D a, Point2D b, Color c = Color::White());

    // ===== lab03 =====

    /**
     * @brief Rysuje okrąg z 8-krotną symetrią (lab03).
     * @param center Środek.
     * @param r Promień.
     * @param c Kolor.
     */
    void drawCircle(Point2D center, int r, Color c);

    /**
     * @brief Rysuje elipsę z 4-krotną symetrią (lab03).
     * @param center Środek.
     * @param rx Promień X.
     * @param ry Promień Y.
     * @param c Kolor.
     */
    void drawEllipse(Point2D center, int rx, int ry, Color c);

    /**
     * @brief Rysuje wielokąt (łamana zamknięta).
     * @param pts Wierzchołki.
     * @param c Kolor.
     */
    void drawPolygon(const std::vector<Point2D>& pts, Color c);

    // ===== lab03 — wypełnianie =====

    /**
     * @brief Wypełnianie przez spójność (flood fill) — iteracyjne.
     * @param x Współrzędna X ziarna.
     * @param y Współrzędna Y ziarna.
     * @param fill Kolor wypełnienia.
     */
    void floodFill(int x, int y, Color fill);

    /**
     * @brief Wypełnianie przez spójność z jawnym kolorem tła.
     */
    void floodFill(int x, int y, Color fill, Color background);

    /**
     * @brief Wypełnianie z kontrolą parzystości (scanline polygon fill).
     * @param pts Wierzchołki wielokąta.
     * @param fill Kolor wypełnienia.
     */
    void scanlineFill(const std::vector<Point2D>& pts, Color fill);

    /// @brief Zwraca bufor (np. do zapisu).
    sf::Image& getBuffer() { return buffer; }
    /// @brief Zwraca szerokość bufora.
    unsigned getWidth() const { return buffer.getSize().x; }
    /// @brief Zwraca wysokość bufora.
    unsigned getHeight() const { return buffer.getSize().y; }
};

} // namespace engine2d


#endif //SILNIK2D_RENDERER_H
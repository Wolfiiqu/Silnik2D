

#ifndef SILNIK2D_BITMAP_H
#define SILNIK2D_BITMAP_H


#pragma once
/**
 * @file Bitmap.hpp
 * @brief Bitmapa (lab05).
 * @author Osoba C
 * @date 2026
 */

#include <SFML/Graphics.hpp>
#include <string>
#include "Color.h"

namespace engine2d {

    /**
     * @brief Bitmapa — obraz 2D z możliwością odczytu/zapisu pikseli.
     */
    class Bitmap {
    private:
        sf::Image image;       ///< Obraz.
        sf::Texture texture;   ///< Tekstura do wyświetlania.
        bool loaded = false;   ///< Czy załadowana.

    public:
        /**
         * @brief Ładuje bitmapę z pliku.
         * @param path Ścieżka.
         * @return true jeśli się udało.
         */
        bool loadFromFile(const std::string& path);

        /**
         * @brief Zapisuje bitmapę do pliku.
         * @param path Ścieżka.
         * @return true jeśli się udało.
         */
        bool saveToFile(const std::string& path) const;

        /// @brief Szerokość w pikselach.
        unsigned getWidth() const { return image.getSize().x; }
        /// @brief Wysokość w pikselach.
        unsigned getHeight() const { return image.getSize().y; }

        /**
         * @brief Zwraca kolor piksela.
         * @param x Współrzędna X.
         * @param y Współrzędna Y.
         */
        Color getPixel(int x, int y) const;

        /**
         * @brief Ustawia kolor piksela.
         * @param x Współrzędna X.
         * @param y Współrzędna Y.
         * @param c Kolor.
         */
        void setPixel(int x, int y, Color c);

        /// @brief Zwraca teksturę (dla SpriteObject).
        const sf::Texture& getTexture() const { return texture; }
        /// @brief Zwraca obraz.
        const sf::Image& getImage() const { return image; }
    };

} // namespace engine2d

#endif //SILNIK2D_BITMAP_H
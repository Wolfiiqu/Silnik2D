
#pragma once
/**
 * @file Color.h
 * @brief Kolor RGBA (lab03).
 * @author Osoba B
 * @date 2026
 */

namespace engine2d {

    /**
     * @brief Kolor w formacie RGBA (8 bit na kanał).
     */


    struct Color {
        unsigned char r; ///< Czerwony (0-255).
        unsigned char g; ///< Zielony (0-255).
        unsigned char b; ///< Niebieski (0-255).
        unsigned char a; ///< Alfa (0-255), domyślnie 255.


        Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255)
            : r(r), g(g), b(b), a(a) {}

        /// @brief Kolor czerwony.
        static Color Red()   { return {255, 0, 0, 255}; }
        /// @brief Kolor zielony.
        static Color Green() { return {0, 255, 0, 255}; }
        /// @brief Kolor niebieski.
        static Color Blue()  { return {0, 0, 255, 255}; }
        /// @brief Kolor czarny.
        static Color Black() { return {0, 0, 0, 255}; }
        /// @brief Kolor bialy.
        static Color White() { return {255, 255, 255, 255}; }

    };

}





#pragma once
/**
 * @file BitmapHandler.hpp
 * @brief Cache bitmap (lab05).
 * @author Osoba C
 * @date 2026
 */

#include <unordered_map>
#include <string>
#include "Bitmap.h"

namespace engine2d {

    /**
     * @brief Menedżer bitmap — ładuje i cachuje bitmapy po ścieżce.
     */
    class BitmapHandler {
    private:
        std::unordered_map<std::string, Bitmap> cache;

    public:
        /**
         * @brief Ładuje bitmapę (lub zwraca z cache).
         * @param path Ścieżka.
         * @return Referencja do bitmapy.
         */
        Bitmap& load(const std::string& path);

        /**
         * @brief Usuwa bitmapę z cache.
         * @param path Ścieżka.
         */
        void unload(const std::string& path);

        /**
         * @brief Zwraca bitmapę z cache lub nullptr.
         * @param path Ścieżka.
         */
        Bitmap* get(const std::string& path);
    };

}



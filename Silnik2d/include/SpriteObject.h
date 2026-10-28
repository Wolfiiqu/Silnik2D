

#pragma once
/**
 * @file SpriteObject.hpp
 * @brief Sprite animowany (lab05).
 * @author Osoba C
 * @date 2026
 */

#include <vector>
#include "BitmapObject.h"
#include "AnimatedObject.h"

namespace engine2d {

    /**
     * @brief Sprite — obiekt bitmapowy z animacją klatkową.
     */
    class SpriteObject : public BitmapObject, public AnimatedObject {
    private:
        std::vector<Bitmap*> frames; ///< Klatki animacji.
        int currentFrame = 0;        ///< Aktualna klatka.
        float frameTime = 0.1f;      ///< Czas klatki (sekundy).
        float elapsed = 0.0f;        ///< Zegar klatki.
        bool loop = true;            ///< Czy zapętlać.

    public:
        /**
         * @brief Dodaje klatkę animacji.
         * @param b Wskaźnik do bitmapy.
         */
        void addFrame(Bitmap* b);

        /**
         * @brief Ustawia czas trwania klatki.
         * @param t Czas w sekundach.
         */
        void setFrameTime(float t) { frameTime = t; }

        /// @brief Aktualizuje animację.
        void animate(float dt) override;

        /// @brief Rysuje aktualną klatkę.
        void draw(Renderer& r) override;
    };

} // namespace engine2d


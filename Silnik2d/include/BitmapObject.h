//
// Created by user on 19.10.2026.
//

#ifndef SILNIK2D_BITMAPOBJECT_H
#define SILNIK2D_BITMAPOBJECT_H
#pragma once
/**
 * @file BitmapObject.hpp
 * @brief Obiekt rysowany bitmapą (lab05).
 * @author Osoba C
 * @date 2026
 */

#include <SFML/Graphics.hpp>
#include "DrawableObject.h"
#include "TransformableObject.h"
#include "Bitmap.h"

namespace engine2d {

    /**
     * @brief Obiekt gry rysowany za pomocą bitmapy.
     */
    class BitmapObject : virtual public DrawableObject,
                         virtual public TransformableObject {
    protected:
        Bitmap* bitmap = nullptr; ///< Wskaźnik do bitmapy (nie właściciel).

    public:
        virtual ~BitmapObject() = default;

        /**
         * @brief Ustawia bitmapę obiektu.
         * @param b Wskaźnik do bitmapy.
         */
        void setBitmap(Bitmap* b) { bitmap = b; }

        /// @brief Rysuje bitmapę z uwzględnieniem transformacji.
        void draw(Renderer& r) override;
    };

} // namespace engine2d
#endif //SILNIK2D_BITMAPOBJECT_H
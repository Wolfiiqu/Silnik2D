//
// Created by user on 19.10.2026.
//

#ifndef SILNIK2D_DRAWABLEOBJECT_H
#define SILNIK2D_DRAWABLEOBJECT_H


#pragma once
/**
 * @file DrawableObject.hpp
 * @brief Interfejs obiektów rysowalnych (lab04).
 * @author Osoba B
 * @date 2026
 */

#include "GameObject.h"

namespace engine2d {

    class Renderer;

    /**
     * @brief Interfejs obiektów, które można narysować.
     */
    class DrawableObject : virtual public GameObject {
    public:
        virtual ~DrawableObject() = default;

        /**
         * @brief Rysuje obiekt.
         * @param r Referencja do Renderera.
         */
        virtual void draw(Renderer& r) = 0;
    };

} // namespace engine2d

#endif //SILNIK2D_DRAWABLEOBJECT_H
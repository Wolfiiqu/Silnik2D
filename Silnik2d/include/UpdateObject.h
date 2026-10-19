
#ifndef SILNIK2D_UPDATEOBJECT_H
#define SILNIK2D_UPDATEOBJECT_H

#pragma once
/**
 * @file UpdatableObject.h
 * @brief Interfejs obiektów aktualizowalnych (lab04).
 * @author Osoba B
 * @date 2026
 */

#include "GameObject.h"

namespace engine2d {

    /**
     * @brief Interfejs obiektów, które można aktualizować (logika gry).
     */
    class UpdatableObject : virtual public GameObject {
    public:
        virtual ~UpdatableObject() = default;

        /**
         * @brief Aktualizuje stan obiektu.
         * @param dt Delta czasu w sekundach.
         */
        virtual void update(float dt) = 0;
    };

} // namespace engine2d

#endif //SILNIK2D_UPDATEOBJECT_H
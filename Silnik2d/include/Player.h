#ifndef SILNIK2D_PLAYER_H
#define SILNIK2D_PLAYER_H


#pragma once
/**
 * @file Player.hpp
 * @brief Gracz sterowany klawiaturą (lab04 + lab05).
 * @author Osoba C
 * @date 2026
 */

#include "Sprite.h"
#include "UpdateObject.h"
#include "InputManager.h"

namespace engine2d {

    /**
     * @brief Gracz — sprite sterowany WSAD.
     */
    class Player : public SpriteObject, public UpdatableObject {
    private:
        InputManager* input = nullptr; ///< Wskaźnik do inputu.
        float speed = 200.0f;          ///< Prędkość (piksele/s).

    public:
        /**
         * @brief Konstruktor.
         * @param input Wskaźnik do InputManagera.
         */
        explicit Player(InputManager* input) : input(input) {}

        /**
         * @brief Aktualizuje pozycję gracza na podstawie WSAD.
         * @param dt Delta czasu.
         */
        void update(float dt) override;
    };

} // namespace engine2d

#endif //SILNIK2D_PLAYER_H
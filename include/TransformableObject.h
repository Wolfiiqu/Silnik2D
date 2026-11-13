

#pragma once
/**
 * @file TransformableObject.hpp
 * @brief Interfejs dla obiektów podlegających przekształceniom (lab04).
 * @author Osoba A
 * @date 2026
 */

#include "Transform2D.h"
#include "GameObject.h"

namespace engine2d {

    /**
     * @brief Interfejs obiektów, które można przekształcać geometrycznie.
     *
     * Dziedziczy wirtualnie po GameObject (lab04 str.6 — unikanie diamentu).
     * Domyślna implementacja oparta o Transform2D.
     */
    class TransformableObject : virtual public GameObject {
    protected:
        Transform2D transform; ///< Macierz transformacji obiektu.

    public:
        /// @brief Wirtualny destruktor.
        virtual ~TransformableObject() = default;

        /**
         * @brief Translacja obiektu.
         * @param tx Przesunięcie X.
         * @param ty Przesunięcie Y.
         */
        virtual void translate(float tx, float ty) { transform.translate(tx, ty); }

        /**
         * @brief Rotacja obiektu.
         * @param deg Kąt w stopniach.
         */
        virtual void rotate(float deg) { transform.rotate(deg); }

        /**
         * @brief Skalowanie obiektu.
         * @param kx Współczynnik X.
         * @param ky Współczynnik Y.
         */
        virtual void scale(float kx, float ky) { transform.scale(kx, ky); }

        /// @brief Zwraca referencję do macierzy transformacji.
        const Transform2D& getTransform() const { return transform; }
        /// @brief Resetuje transformację do identity.
        void resetTransform() { transform.reset(); }
    };

} // namespace engine2d


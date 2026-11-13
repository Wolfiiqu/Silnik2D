
#pragma once


namespace engine2d {

    /// Liczba pi (float).
    constexpr float PI = 3.14159265358979323846f;

    /**
     * @brief Konwersja stopni na radiany.
     * @param deg Kąt w stopniach.
     * @return Kąt w radianach.
     */
    inline float degToRad(float deg) { return deg * PI / 180.0f; }

    /**
     * @brief Konwersja radianów na stopnie.
     * @param rad Kąt w radianach.
     * @return Kąt w stopniach.
     */
    inline float radToDeg(float rad) { return rad * 180.0f / PI; }

    /**
     * @brief Interpolacja liniowa.
     * @param a Wartość początkowa (t=0).
     * @param b Wartość końcowa (t=1).
     * @param t Współczynnik interpolacji.
     * @return Wartość pośrednia.
     */
    inline float lerp(float a, float b, float t) { return a + (b - a) * t; }

    /**
     * @brief Ogranicza wartość do przedziału [lo, hi].
     * @param v Wartość wejściowa.
     * @param lo Dolna granica.
     * @param hi Górna granica.
     * @return Wartość ograniczona.
     */
    inline float clamp(float v, float lo, float hi) {
        return v < lo ? lo : (v > hi ? hi : v);
    }

    /**
     * @brief Porównanie floatów z tolerancją.
     * @param a Pierwsza wartość.
     * @param b Druga wartość.
     * @param eps Tolerancja (domyślnie 1e-5).
     * @return true jeśli |a-b| < eps.
     */
    inline bool approxEqual(float a, float b, float eps = 1e-5f) {
        float d = a - b;
        return (d < 0 ? -d : d) < eps;
    }

}


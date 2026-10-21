

#include "../include/Point2D.h"


#include "Point2D.h"
#include "MathUtils.h"
#include "Renderer.h"
#include <cmath>

namespace engine2d {

// ===== lab04 str.3 — translacja =====
// x2 = x1 + tx ; y2 = y1 + ty
void Point2D::translate(float tx, float ty) {
    x += tx;
    y += ty;
}

// ===== lab04 str.3-4 — rotacja względem (0,0) =====
// Wzory z instrukcji:
//   x2 = x1*cos(a) - y1*sin(a)
//   y2 = x1*sin(a) + y1*cos(a)
// Kompensacja Y-down: odwracamy znak sinusa w drugim równaniu,
// żeby obrót dodatni wyglądał wizualnie jak CCW na ekranie.
void Point2D::rotate(float deg) {
    float a = degToRad(deg);
    float c = std::cos(a);
    float s = std::sin(a);
    float x1 = x, y1 = y;
    x =  x1 * c - y1 * s;
    y = -x1 * s + y1 * c;
}

// ===== lab04 str.5 — jednokładność względem (0,0) =====
// x2 = x1*kx ; y2 = y1*ky
void Point2D::scale(float kx, float ky) {
    x *= kx;
    y *= ky;
}

// ===== lab04 str.4 — rotacja wokół (x0,y0) =====
// x2 = x0 + (x1-x0)*cos - (y1-y0)*sin
// y2 = y0 + (x1-x0)*sin + (y1-y0)*cos
void Point2D::rotateAround(const Point2D& pivot, float deg) {
    float a = degToRad(deg);
    float c = std::cos(a);
    float s = std::sin(a);
    float dx = x - pivot.x;
    float dy = y - pivot.y;
    x = pivot.x + dx * c - dy * s;
    y = pivot.y - dx * s + dy * c;   // Y-down
}

// ===== lab04 str.5 — jednokładność względem (x0,y0) =====
// x2 = x1*kx + (1-kx)*x0
// y2 = y1*ky + (1-ky)*y0
void Point2D::scaleAround(const Point2D& pivot, float kx, float ky) {
    x = x * kx + (1.0f - kx) * pivot.x;
    y = y * ky + (1.0f - ky) * pivot.y;
}

Point2D Point2D::translated(float tx, float ty) const {
    Point2D p = *this;
    p.translate(tx, ty);
    return p;
}

Point2D Point2D::rotated(float deg) const {
    Point2D p = *this;
    p.rotate(deg);
    return p;
}

Point2D Point2D::scaled(float kx, float ky) const {
    Point2D p = *this;
    p.scale(kx, ky);
    return p;
}

// lab02: rysowanie punktu = pojedynczy piksel
void Point2D::draw(Renderer& r) const {
    r.drawPixel(static_cast<int>(x), static_cast<int>(y));
}

float Point2D::distance(const Point2D& o) const {
    float dx = x - o.x;
    float dy = y - o.y;
    return std::sqrt(dx * dx + dy * dy);
}

} // namespace engine2d
    #include "Transform2D.h"
#include "MathUtils.h"
#include <cmath>

namespace engine2d {

Transform2D::Transform2D() {
    reset();
}

void Transform2D::reset() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j] = (i == j) ? 1.0f : 0.0f;
}

Transform2D Transform2D::translation(float tx, float ty) {
    Transform2D t;
    t.m[0][2] = tx;
    t.m[1][2] = ty;
    return t;
}

Transform2D Transform2D::rotation(float deg) {
    Transform2D t;
    float a = degToRad(deg);
    float c = std::cos(a);
    float s = std::sin(a);
    // Kompensacja Y-down — tak samo jak w Point2D::rotate
    t.m[0][0] =  c;
    t.m[0][1] = -s;
    t.m[1][0] = -s;
    t.m[1][1] =  c;
    return t;
}

Transform2D Transform2D::scaling(float kx, float ky) {
    Transform2D t;
    t.m[0][0] = kx;
    t.m[1][1] = ky;
    return t;
}

Transform2D Transform2D::operator*(const Transform2D& o) const {
    Transform2D r;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            r.m[i][j] = 0.0f;
            for (int k = 0; k < 3; ++k)
                r.m[i][j] += m[i][k] * o.m[k][j];
        }
    }
    return r;
}

Point2D Transform2D::apply(const Point2D& p) const {
    float x = m[0][0] * p.x + m[0][1] * p.y + m[0][2];
    float y = m[1][0] * p.x + m[1][1] * p.y + m[1][2];
    return {x, y};
}

Point2D Transform2D::applyVector(const Point2D& v) const {
    float x = m[0][0] * v.x + m[0][1] * v.y;
    float y = m[1][0] * v.x + m[1][1] * v.y;
    return {x, y};
}

void Transform2D::translate(float tx, float ty) {
    *this = translation(tx, ty) * (*this);
}

void Transform2D::rotate(float deg) {
    *this = rotation(deg) * (*this);
}

void Transform2D::scale(float kx, float ky) {
    *this = scaling(kx, ky) * (*this);
}

Transform2D Transform2D::inverse() const {
    // Dla macierzy afinicznej:
    // [ a c e ]
    // [ b d f ]
    // [ 0 0 1 ]
    float a = m[0][0], c = m[0][1], e = m[0][2];
    float b = m[1][0], d = m[1][1], f = m[1][2];

    float det = a * d - b * c;
    Transform2D r;
    if (std::fabs(det) < 1e-8f) return r; // macierz osobliwa → identity
    float inv = 1.0f / det;

    r.m[0][0] =  d * inv;
    r.m[0][1] = -c * inv;
    r.m[1][0] = -b * inv;
    r.m[1][1] =  a * inv;
    r.m[0][2] = -(r.m[0][0] * e + r.m[0][1] * f);
    r.m[1][2] = -(r.m[1][0] * e + r.m[1][1] * f);
    return r;
}

}
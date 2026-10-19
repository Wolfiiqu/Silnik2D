#include "../include/Line.h"
#include "Renderer.h"

namespace engine2d {

    // lab04 str.2: "przekształcenie wszystkich punktów odcinka w dużo prostszy
    // sposób — poprzez przetransformowanie tylko końców odcinka"
    void LineSegment::translate(float tx, float ty) {
        p1.translate(tx, ty);
        p2.translate(tx, ty);
    }

    void LineSegment::rotate(float deg) {
        p1.rotate(deg);
        p2.rotate(deg);
    }

    void LineSegment::rotateAround(const Point2D& pivot, float deg) {
        p1.rotateAround(pivot, deg);
        p2.rotateAround(pivot, deg);
    }

    void LineSegment::scale(float kx, float ky) {
        p1.scale(kx, ky);
        p2.scale(kx, ky);
    }

    void LineSegment::scaleAround(const Point2D& pivot, float kx, float ky) {
        p1.scaleAround(pivot, kx, ky);
        p2.scaleAround(pivot, kx, ky);
    }

    // lab02: renderowanie — delegacja do algorytmu przyrostowego z lab02
    // (Renderer::drawLine implementuje Osoba B)
    void LineSegment::draw(Renderer& r) const {
        r.drawLine(p1, p2);
    }

} // namespace engine2d

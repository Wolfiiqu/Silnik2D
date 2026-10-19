#include "Triangle.h"
#include "Renderer.h"

namespace engine2d {

    void Triangle::draw(Renderer& r) {
        Point2D pa = transform.apply(a);
        Point2D pb = transform.apply(b);
        Point2D pc = transform.apply(c);

        if (filled) {
            std::vector<Point2D> pts = {pa, pb, pc};
            r.scanlineFill(pts, color);
        } else {
            r.drawLine(pa, pb, color);
            r.drawLine(pb, pc, color);
            r.drawLine(pc, pa, color);
        }
    }

} // namespace engine2d
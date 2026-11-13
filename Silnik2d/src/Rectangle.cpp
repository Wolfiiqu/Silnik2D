
#include "Rectangle.h"
#include "Renderer.h"

namespace engine2d {

    void Rectangle::draw(Renderer& r) {
        if (!visible) {return;}
        Point2D p1 = transform.apply({0, 0});
        Point2D p2 = transform.apply({w, 0});
        Point2D p3 = transform.apply({w, h});
        Point2D p4 = transform.apply({0, h});

        if (filled) {
            std::vector<Point2D> pts = {p1, p2, p3, p4};
            r.scanlineFill(pts, color);
        } else {
            r.drawLine(p1, p2, color);
            r.drawLine(p2, p3, color);
            r.drawLine(p3, p4, color);
            r.drawLine(p4, p1, color);
        }
    }

} // namespace engine2d
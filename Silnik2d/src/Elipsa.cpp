#include "Elipsa.h"
#include "Renderer.h"

namespace engine2d {

    void Ellipse::draw(Renderer& r) {
        if (!visible) {return;}
        Point2D center = transform.apply({0, 0});
        r.drawEllipse(center, (int)rx, (int)ry, color);
    }

} // namespace engine2d
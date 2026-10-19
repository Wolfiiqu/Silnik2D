#include "Circle.h"
#include "Renderer.h"
#include <cmath>

namespace engine2d {

    void Circle::draw(Renderer& r) {
        Point2D center = transform.apply({0, 0});
        if (filled) {
            for (int y = -radius; y <= radius; ++y) {
                int x = (int)std::round(std::sqrt(radius * radius - y * y));
                r.drawLine({center.x - x, center.y + y}, {center.x + x, center.y + y}, color);
            }
        } else {
            r.drawCircle(center, (int)radius, color);
        }
    }

} // namespace engine2d
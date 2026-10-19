#include "Polygon.h"
#include "Renderer.h"

namespace engine2d {

    void Polygon::draw(Renderer& r) {
        std::vector<Point2D> pts;
        pts.reserve(points.size());
        for (const auto& p : points)
            pts.push_back(transform.apply(p));

        if (filled) {
            r.scanlineFill(pts, color);
        } else {
            r.drawPolygon(pts, color);
        }
    }

} // namespace engine2d
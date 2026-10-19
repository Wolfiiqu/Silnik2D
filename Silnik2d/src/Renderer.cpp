#include "Renderer.h"
#include "MathUtils.h"
#include <cmath>
#include <stack>

namespace engine2d {

Renderer::Renderer(sf::RenderWindow& w) : window(w) {
    auto size = w.getSize();
    buffer.create(size.x, size.y, sf::Color::Black);
    texture.create(size.x, size.y);
    screenSprite.setTexture(texture);
}

void Renderer::clear(Color c) {
    auto size = buffer.getSize();
    for (unsigned y = 0; y < size.y; ++y)
        for (unsigned x = 0; x < size.x; ++x)
            buffer.setPixel(x, y, sf::Color(c.r, c.g, c.b, c.a));
}

void Renderer::display() {
    texture.update(buffer);
    window.draw(screenSprite);
}

// ===== lab02 =====

void Renderer::drawPixel(int x, int y, Color c) {
    if (x < 0 || y < 0) return;
    auto size = buffer.getSize();
    if ((unsigned)x >= size.x || (unsigned)y >= size.y) return;
    buffer.setPixel(x, y, sf::Color(c.r, c.g, c.b, c.a));
}

// Algorytm przyrostowy z lab02
void Renderer::drawLine(Point2D a, Point2D b, Color c) {
    int x0 = (int)a.x, y0 = (int)a.y;
    int x1 = (int)b.x, y1 = (int)b.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}

// ===== lab03 — okrąg z 8-krotną symetrią =====

static void plotCircle8(Renderer& r, int xc, int yc, int x, int y, Color c) {
    r.drawPixel(xc + x, yc + y, c);
    r.drawPixel(xc - x, yc + y, c);
    r.drawPixel(xc + x, yc - y, c);
    r.drawPixel(xc - x, yc - y, c);
    r.drawPixel(xc + y, yc + x, c);
    r.drawPixel(xc - y, yc + x, c);
    r.drawPixel(xc + y, yc - x, c);
    r.drawPixel(xc - y, yc - x, c);
}

void Renderer::drawCircle(Point2D center, int r, Color c) {
    int xc = (int)center.x, yc = (int)center.y;
    int x = 0, y = r;
    int d = 3 - 2 * r;
    plotCircle8(*this, xc, yc, x, y, c);
    while (y >= x) {
        ++x;
        if (d > 0) { --y; d = d + 4 * (x - y) + 10; }
        else       { d = d + 4 * x + 6; }
        plotCircle8(*this, xc, yc, x, y, c);
    }
}

// ===== lab03 — elipsa z 4-krotną symetrią =====

static void plotEllipse4(Renderer& r, int xc, int yc, int x, int y, Color c) {
    r.drawPixel(xc + x, yc + y, c);
    r.drawPixel(xc - x, yc + y, c);
    r.drawPixel(xc + x, yc - y, c);
    r.drawPixel(xc - x, yc - y, c);
}

void Renderer::drawEllipse(Point2D center, int rx, int ry, Color c) {
    int xc = (int)center.x, yc = (int)center.y;
    for (int x = -rx; x <= rx; ++x) {
        float t = 1.0f - (float)(x * x) / (float)(rx * rx);
        if (t < 0) continue;
        int y = (int)std::round(ry * std::sqrt(t));
        plotEllipse4(*this, xc, yc, x, y, c);
    }
}

// ===== lab03 — wielokąt =====

void Renderer::drawPolygon(const std::vector<Point2D>& pts, Color c) {
    if (pts.size() < 2) return;
    for (size_t i = 0; i < pts.size(); ++i) {
        size_t j = (i + 1) % pts.size();
        drawLine(pts[i], pts[j], c);
    }
}

// ===== lab03 — flood fill (iteracyjny) =====

void Renderer::floodFill(int x, int y, Color fill) {
    auto size = buffer.getSize();
    if (x < 0 || y < 0 || (unsigned)x >= size.x || (unsigned)y >= size.y) return;
    sf::Color bg = buffer.getPixel(x, y);
    floodFill(x, y, fill, Color(bg.r, bg.g, bg.b, bg.a));
}

void Renderer::floodFill(int x, int y, Color fill, Color bg) {
    auto size = buffer.getSize();
    sf::Color target(bg.r, bg.g, bg.b, bg.a);
    sf::Color replacement(fill.r, fill.g, fill.b, fill.a);
    if (target == replacement) return;

    std::stack<std::pair<int, int>> stack;
    stack.push({x, y});

    while (!stack.empty()) {
        auto [px, py] = stack.top();
        stack.pop();
        if (px < 0 || py < 0 || (unsigned)px >= size.x || (unsigned)py >= size.y) continue;
        if (buffer.getPixel(px, py) != target) continue;
        buffer.setPixel(px, py, replacement);
        stack.push({px + 1, py});
        stack.push({px - 1, py});
        stack.push({px, py + 1});
        stack.push({px, py - 1});
    }
}

// ===== lab03 — scanline fill (kontrola parzystości) =====

void Renderer::scanlineFill(const std::vector<Point2D>& pts, Color fill) {
    if (pts.size() < 3) return;

    int minY = (int)pts[0].y, maxY = (int)pts[0].y;
    for (auto& p : pts) {
        if ((int)p.y < minY) minY = (int)p.y;
        if ((int)p.y > maxY) maxY = (int)p.y;
    }

    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> intersections;
        for (size_t i = 0; i < pts.size(); ++i) {
            size_t j = (i + 1) % pts.size();
            float y1 = pts[i].y, y2 = pts[j].y;
            float x1 = pts[i].x, x2 = pts[j].x;

            // pomijamy krawędzie poziome (problem brzegowy z lab03)
            if (y1 == y2) continue;
            if ((y >= y1 && y < y2) || (y >= y2 && y < y1)) {
                float t = (y - y1) / (y2 - y1);
                intersections.push_back((int)std::round(x1 + t * (x2 - x1)));
            }
        }
        std::sort(intersections.begin(), intersections.end());
        for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
            for (int x = intersections[i]; x <= intersections[i + 1]; ++x)
                drawPixel(x, y, fill);
        }
    }
}

} // namespace engine2d
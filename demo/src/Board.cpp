#include "..\demo\include\Board.h"

namespace engine2d {
    class Renderer;
}
namespace game {
    using namespace engine2d;

    bool Board::contains(float x, float y) {
        return x >= GameConfig::BOARD_X && x <= GameConfig::BOARD_X + GameConfig::BOARD_W &&
               y >= GameConfig::BOARD_Y && y <= GameConfig::BOARD_Y + GameConfig::BOARD_H;
    }

    void Board::clamp(float& x, float& y, float w, float h) {
        float minX = GameConfig::BOARD_X;
        float minY = GameConfig::BOARD_Y;
        float maxX = GameConfig::BOARD_X + GameConfig::BOARD_W - w;
        float maxY = GameConfig::BOARD_Y + GameConfig::BOARD_H - h;
        if (x < minX) x = minX;
        if (y < minY) y = minY;
        if (x > maxX) x = maxX;
        if (y > maxY) y = maxY;
    }

    void Board::draw(Renderer& r) {
        // Wypełnienie planszy (ciemny prostokąt) — przez scanlineFill
        std::vector<Point2D> rect = {
            {GameConfig::BOARD_X, GameConfig::BOARD_Y},
            {GameConfig::BOARD_X + GameConfig::BOARD_W, GameConfig::BOARD_Y},
            {GameConfig::BOARD_X + GameConfig::BOARD_W, GameConfig::BOARD_Y + GameConfig::BOARD_H},
            {GameConfig::BOARD_X, GameConfig::BOARD_Y + GameConfig::BOARD_H}
        };
        r.scanlineFill(rect, Color(25, 25, 40));  // ciemne tło planszy

        // Ramka
        Point2D tl(GameConfig::BOARD_X, GameConfig::BOARD_Y);
        Point2D tr(GameConfig::BOARD_X + GameConfig::BOARD_W, GameConfig::BOARD_Y);
        Point2D br(GameConfig::BOARD_X + GameConfig::BOARD_W, GameConfig::BOARD_Y + GameConfig::BOARD_H);
        Point2D bl(GameConfig::BOARD_X, GameConfig::BOARD_Y + GameConfig::BOARD_H);
        Color c(100, 100, 150);
        r.drawLine(tl, tr, c);
        r.drawLine(tr, br, c);
        r.drawLine(br, bl, c);
        r.drawLine(bl, tl, c);
    }

} // namespace game
#include "../demo/include/BoardObject.h"
#include "../demo/include/Board.h"
#include "../demo/include/GameConfig.h"
#include <vector>

namespace game {
    using namespace engine2d;

    void BoardObject::draw(Renderer& r) {
        // 1. Wypełnienie planszy (ciemne tło)
        std::vector<Point2D> rect = {
            {GameConfig::BOARD_X, GameConfig::BOARD_Y},
            {GameConfig::BOARD_X + GameConfig::BOARD_W, GameConfig::BOARD_Y},
            {GameConfig::BOARD_X + GameConfig::BOARD_W, GameConfig::BOARD_Y + GameConfig::BOARD_H},
            {GameConfig::BOARD_X, GameConfig::BOARD_Y + GameConfig::BOARD_H}
        };
        r.scanlineFill(rect, Color(25, 25, 40));

        // 2. Ramka (delegacja do Board::draw)
        Board::draw(r);
    }

} // namespace game
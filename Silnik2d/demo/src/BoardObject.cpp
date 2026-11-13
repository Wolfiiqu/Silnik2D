#include "../demo/include/BoardObject.h"
#include "../demo/include/Board.h"
#include "../demo/include/GameConfig.h"
#include <vector>

namespace game {
    using namespace engine2d;

    void BoardObject::draw(Renderer& r) {

        Board::draw(r);
    }

} // namespace game
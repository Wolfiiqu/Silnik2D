#include "../include/Starfield.h"

namespace game {
    using namespace engine2d;

    void Starfield::draw(Renderer& r) {

        r.clear(Color(15, 15, 30));


        srand(123);
        for (int i = 0; i < 200; ++i) {
            int x = rand() % GameConfig::WINDOW_W;
            int y = rand() % GameConfig::WINDOW_H;
            Point2D(x, y).draw(r);
        }
        srand(static_cast<unsigned>(::time(nullptr)));
    }

}
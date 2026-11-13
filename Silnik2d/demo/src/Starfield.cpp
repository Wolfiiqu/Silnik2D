#include "../include/Starfield.h"
#include "../include/GameConfig.h"
#include <cstdlib>
#include <ctime>

namespace game {
    using namespace engine2d;

    Starfield::Starfield() {
        std::srand(123);
        for (int i = 0; i < 200; ++i) {
            int x = std::rand() % GameConfig::WINDOW_W;
            int y = std::rand() % GameConfig::WINDOW_H;
            stars.push_back(Point2D(x, y));
        }
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void Starfield::draw(Renderer& r) {
        r.clear(Color(15, 15, 30));
        for (const auto& star : stars) {
            star.draw(r);
        }
    }
}
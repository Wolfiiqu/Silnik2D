#include "Bitmap.h"

namespace engine2d {

    bool Bitmap::loadFromFile(const std::string& path) {
        if (!image.loadFromFile(path)) return false;
        texture.loadFromImage(image);
        loaded = true;
        return true;
    }

    bool Bitmap::saveToFile(const std::string& path) const {
        return image.saveToFile(path);
    }

    Color Bitmap::getPixel(int x, int y) const {
        sf::Color c = image.getPixel(x, y);
        return Color(c.r, c.g, c.b, c.a);
    }

    void Bitmap::setPixel(int x, int y, Color c) {
        image.setPixel(x, y, sf::Color(c.r, c.g, c.b, c.a));
        texture.update(image);
    }

} // namespace engine2d
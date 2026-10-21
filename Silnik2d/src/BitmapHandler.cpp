#include "../include/BitmapHandler.h"

namespace engine2d {

    Bitmap& BitmapHandler::load(const std::string& path) {
        auto it = cache.find(path);
        if (it != cache.end()) return it->second;
        Bitmap b;
        b.loadFromFile(path);
        auto res = cache.emplace(path, std::move(b));
        return res.first->second;
    }

    void BitmapHandler::unload(const std::string& path) {
        cache.erase(path);
    }

    Bitmap* BitmapHandler::get(const std::string& path) {
        auto it = cache.find(path);
        return (it != cache.end()) ? &it->second : nullptr;
    }

} // namespace engine2d
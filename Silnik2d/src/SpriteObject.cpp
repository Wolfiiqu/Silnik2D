#include "SpriteObject.h"

namespace engine2d {

    void SpriteObject::addFrame(Bitmap* b) {
        frames.push_back(b);
        if (frames.size() == 1) bitmap = b;
    }

    void SpriteObject::animate(float dt) {
        if (frames.size() < 2) return;
        elapsed += dt;
        if (elapsed >= frameTime) {
            elapsed -= frameTime;
            currentFrame++;
            if (currentFrame >= (int)frames.size()) {
                currentFrame = loop ? 0 : (int)frames.size() - 1;
            }
            bitmap = frames[currentFrame];
        }
    }

    void SpriteObject::draw(Renderer& r) {
        BitmapObject::draw(r);
    }

} // namespace engine2d
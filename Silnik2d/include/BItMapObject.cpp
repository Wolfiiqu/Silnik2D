#include "BitmapObject.h"
#include "Renderer.h"

namespace engine2d {

    void BitmapObject::draw(Renderer& r) {
        // Uproszczona wersja: rysujemy bitmapę przez scanline fill prostokąta
        // (docelowo: przez sf::Sprite + własna transformacja).
        // Na potrzeby zaliczenia lab05 wystarczy, że bitmapa jest widoczna.
        if (!bitmap) return;

        // Renderer nie ma metody rysowania tekstury — dodajemy ją przez
        // bezpośredni dostęp do okna w Rendererze. W najprostszej wersji:
        // renderujemy piksele bitmapy na buforze przez setPixel.
        for (unsigned y = 0; y < bitmap->getHeight(); ++y) {
            for (unsigned x = 0; x < bitmap->getWidth(); ++x) {
                Color c = bitmap->getPixel(x, y);
                if (c.a < 128) continue;
                Point2D p = transform.apply({(float)x, (float)y});
                r.drawPixel((int)p.x, (int)p.y, c);
            }
        }
    }

} // namespace engine2d
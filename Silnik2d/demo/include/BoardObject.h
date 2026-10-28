#pragma once
#include "../include/DrawableObject.h"
namespace game {
    /**
     * @brief Obiekt rysujący planszę (tło + ramka).
     *
     * Dzięki temu, że jest DrawableObject, Engine::run rysuje go
     * razem z innymi obiektami. Kolejność dodania do Engine
     * decyduje o kolejności rysowania (pierwszy = pod spodem).
     */
    class BoardObject : public engine2d::DrawableObject {
    public:
        void draw(engine2d::Renderer& r) override;
    };
}

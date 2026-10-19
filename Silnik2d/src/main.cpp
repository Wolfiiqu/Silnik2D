#include <memory>
#include <cstdlib>
#include <ctime>

#include "Engine.h"
#include "Rectangle.h"
#include "UpdateObject.h"
#include "InputManager.h"

using namespace engine2d;

/**
 * @brief Kwadrat poruszający się po planszy.
 *
 * Sterowanie: WSAD. Kwadrat odbija się od krawędzi okna.
 * Dziedziczy po Rectangle (rysowanie) i UpdatableObject (logika).
 */
class MovingSquare : public Rectangle, public UpdatableObject {
private:
    float vx = 150.0f;   ///< Prędkość X (piksele/s).
    float vy = 120.0f;   ///< Prędkość Y (piksele/s).
    float size;
    float windowW, windowH;
    InputManager* input;

public:
    MovingSquare(float size, float windowW, float windowH, InputManager* input)
        : Rectangle(size, size), size(size),
          windowW(windowW), windowH(windowH), input(input) {
        setColor(Color::Green());
        setFilled(true);
        // start w środku okna
        translate(windowW / 2.0f - size / 2.0f,
                  windowH / 2.0f - size / 2.0f);
    }

    void update(float dt) override {
        // Ruch automatyczny (odbijanie od ścian)
        translate(vx * dt, vy * dt);

        // Sprawdź granice — odbij
        Point2D pos = getTransform().apply({0, 0});
        if (pos.x <= 0) {
            vx = std::abs(vx);
            translate(-pos.x, 0);
        }
        if (pos.x + size >= windowW) {
            vx = -std::abs(vx);
            translate(windowW - (pos.x + size), 0);
        }
        if (pos.y <= 0) {
            vy = std::abs(vy);
            translate(0, -pos.y);
        }
        if (pos.y + size >= windowH) {
            vy = -std::abs(vy);
            translate(0, windowH - (pos.y + size));
        }

        // Sterowanie WSAD (dodatkowo, oprócz ruchu automatycznego)
        float manualSpeed = 200.0f * dt;
        if (input) {
            if (input->isKeyDown(sf::Keyboard::A)) translate(-manualSpeed, 0);
            if (input->isKeyDown(sf::Keyboard::D)) translate( manualSpeed, 0);
            if (input->isKeyDown(sf::Keyboard::W)) translate(0, -manualSpeed);
            if (input->isKeyDown(sf::Keyboard::S)) translate(0,  manualSpeed);
        }
    }
};

int main() {
    // Konfiguracja okna
    const int W = 800;
    const int H = 600;

    Engine engine(W, H, "Silnik2D — demo: poruszajacy sie kwadrat");

    // Tworzymy kwadrat 60x60, przekazujemy input z silnika
    auto square = std::make_unique<MovingSquare>(
        60.0f, (float)W, (float)H, &engine.getInput());

    engine.addObject(std::move(square));

    // Uruchamiamy pętlę (blokuje do zamknięcia okna)
    engine.run();

    return 0;
}
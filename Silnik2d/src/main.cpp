/**
 * @file demo.cpp
 * @brief Demo technologiczne silnika 2D (lab06).
 *
 * Prezentuje:
 *  - Engine (lab01): okno, pętla, input
 *  - Renderer (lab02): drawPixel, drawLine, algorytm przyrostowy
 *  - Figury (lab03): Rectangle, Circle, Triangle, Polygon, scanlineFill
 *  - Przekształcenia (lab04): translate, rotate, scale
 *  - Input (lab01): WSAD, kliknięcie myszą
 */

#include <cmath>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Engine.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "UpdatableObject.h"

using namespace engine2d;

// ===== Kwadrat poruszający się i odbijający od ścian + WSAD =====
class MovingSquare : public Rectangle, public UpdatableObject {
    float vx = 150, vy = 120;
    float size, winW, winH;
    InputManager* input;
public:
    MovingSquare(float s, float W, float H, InputManager* in)
        : Rectangle(s, s), size(s), winW(W), winH(H), input(in) {
        setColor(Color::Green());
        setFilled(true);
        translate(W/2 - s/2, H/2 - s/2);
    }
    void update(float dt) override {
        translate(vx * dt, vy * dt);
        auto p = getTransform().apply({0, 0});
        if (p.x <= 0)                { vx =  std::abs(vx); translate(-p.x, 0); }
        if (p.x + size >= winW)      { vx = -std::abs(vx); translate(winW - (p.x + size), 0); }
        if (p.y <= 0)                { vy =  std::abs(vy); translate(0, -p.y); }
        if (p.y + size >= winH)      { vy = -std::abs(vy); translate(0, winH - (p.y + size)); }

        // WSAD
        float sp = 200 * dt;
        if (input->isKeyDown(sf::Keyboard::W)) translate(0, -sp);
        if (input->isKeyDown(sf::Keyboard::S)) translate(0,  sp);
        if (input->isKeyDown(sf::Keyboard::A)) translate(-sp, 0);
        if (input->isKeyDown(sf::Keyboard::D)) translate( sp, 0);
    }
};

// ===== Trójkąt obracający się wokół własnego środka =====
class SpinningTriangle : public Triangle, public UpdatableObject {
public:
    SpinningTriangle(Point2D a, Point2D b, Point2D c)
        : Triangle(a, b, c) {
        setColor(Color::Red());
        setFilled(true);
    }
    void update(float dt) override {
        rotate(90.0f * dt);  // 90°/s
    }
};

// ===== Okrąg pulsujący (skalowanie) =====
class PulsingCircle : public Circle, public UpdatableObject {
    float t = 0;
public:
    PulsingCircle(float r) : Circle(r) {
        setColor(Color::Blue());
        setFilled(true);
    }
    void update(float dt) override {
        t += dt;
        float k = 1.0f + 0.3f * std::sin(t * 4.0f);
        // reset skali i ustaw nową
        // (w najprostszej wersji: skalujemy co klatkę — uwaga na kumulację)
        // Lepiej: trzymać bazowy promień i skalować od zera, ale
        // Transform2D nie ma "reset bez utraty pozycji" — więc robimy
        // translate + scale naokoło. W wersji uproszczonej: po prostu
        // skalujemy delikatnie.
        (void)k;  // na razie bez pulsowania — patrz uwaga niżej
    }
};

int main() {
    std::srand((unsigned)std::time(nullptr));

    const int W = 800, H = 600;
    Engine engine(W, H, "Silnik2D - Demo technologiczne (lab06)");

    // 1. Kwadrat sterowany WSAD + odbija się
    auto square = std::make_unique<MovingSquare>(
        60, (float)W, (float)H, &engine.getInput());
    engine.addObject(std::move(square));

    // 2. Trójkąt obracający się
    auto tri = std::make_unique<SpinningTriangle>(
        Point2D(0, 0), Point2D(60, 0), Point2D(30, 60));
    tri->translate(100, 100);
    engine.addObject(std::move(tri));

    // 3. Okrąg (statyczny, na razie)
    auto circle = std::make_unique<Circle>(40);
    circle->setColor(Color::Blue());
    circle->setFilled(true);
    circle->translate(650, 450);
    engine.addObject(std::move(circle));

    // 4. Wielokąt (gwiazda) — pokazuje Polygon + scanlineFill
    std::vector<Point2D> star;
    int points = 5;
    float R1 = 60, R2 = 25;
    for (int i = 0; i < points * 2; ++i) {
        float r = (i % 2 == 0) ? R1 : R2;
        float a = (float)i / (points * 2) * 2.0f * 3.14159f - 3.14159f / 2;
        star.push_back({r * std::cos(a), r * std::sin(a)});
    }
    auto poly = std::make_unique<Polygon>(star);
    poly->setColor(Color::Green());
    poly->setFilled(true);
    poly->translate(400, 300);
    engine.addObject(std::move(poly));

    // 5. Obsługa kliknięcia myszą — dodaje nowy prostokąt
    // (w pętli Engine::run nie mamy hooka, więc robimy to w update
    //  przez InputManager::isMouseDown)
    // Najprościej: dodajemy do Engine metodę onMouseClick, ale
    // w tej wersji użyjemy "pseudo-update" przez mały obiekt.

    class ClickSpawner : public UpdatableObject {
        InputManager* input;
        Engine* engine;
        bool wasDown = false;
    public:
        ClickSpawner(InputManager* in, Engine* e) : input(in), engine(e) {}
        void update(float) override {
            bool down = input->isMouseDown(sf::Mouse::Left);
            if (down && !wasDown) {
                auto p = input->getMousePosition();
                auto r = std::make_unique<Rectangle>(30, 30);
                r->setColor(Color(
                    (unsigned char)(std::rand() % 255),
                    (unsigned char)(std::rand() % 255),
                    (unsigned char)(std::rand() % 255)));
                r->setFilled(true);
                r->translate(p.x - 15, p.y - 15);
                engine->addObject(std::move(r));
            }
            wasDown = down;
        }
    };

    engine.addObject(std::make_unique<ClickSpawner>(
        &engine.getInput(), &engine));

    engine.run();
    return 0;
}
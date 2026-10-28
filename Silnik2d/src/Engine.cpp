#include "Engine.h"
#include "UpdatableObject.h"
#include "DrawableObject.h"
#include <algorithm>

namespace engine2d {

    Engine::Engine(int width, int height, const std::string& title)
        : window(sf::VideoMode(width, height), title),
          renderer(window) {
        window.setFramerateLimit(60);
    }

    void Engine::run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                input.handleEvent(event);
            }

            float dt = clock.restart().asSeconds();

            if (updateCallback) updateCallback(dt);

            for (auto& obj : objects) {
                if (auto u = dynamic_cast<UpdatableObject*>(obj.get()))
                    u->update(dt);
            }

            renderer.clear();
            for (auto& obj : objects) {
                if (auto d = dynamic_cast<DrawableObject*>(obj.get()))
                    d->draw(renderer);
            }
            renderer.display();   // window.draw(screenSprite)

            // === HUD z sf::Text (rysuje na window) ===
            if (postRenderCallback) postRenderCallback(window);

            window.display();
            input.endFrame();
        }
    }

    void Engine::addObject(std::unique_ptr<GameObject> obj) {
        objects.push_back(std::move(obj));
    }

}
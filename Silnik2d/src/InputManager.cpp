
#include "InputManager.h"

namespace engine2d {

    void InputManager::handleEvent(const sf::Event& e) {
        if (e.type == sf::Event::KeyPressed) {
            pressed.insert(e.key.code);
            justPressed.insert(e.key.code);
        } else if (e.type == sf::Event::KeyReleased) {
            pressed.erase(e.key.code);
        } else if (e.type == sf::Event::MouseButtonPressed) {
            mousePressed.insert(e.mouseButton.button);
        } else if (e.type == sf::Event::MouseButtonReleased) {
            mousePressed.erase(e.mouseButton.button);
        } else if (e.type == sf::Event::MouseMoved) {
            mousePos = Point2D((float)e.mouseMove.x, (float)e.mouseMove.y);
        }
    }

    void InputManager::endFrame() {
        justPressed.clear();
    }

    bool InputManager::isKeyDown(sf::Keyboard::Key k) const {
        return pressed.count(k) > 0;
    }

    bool InputManager::isKeyJustPressed(sf::Keyboard::Key k) const {
        return justPressed.count(k) > 0;
    }

    bool InputManager::isMouseDown(sf::Mouse::Button b) const {
        return mousePressed.count(b) > 0;
    }

} // namespace engine2d
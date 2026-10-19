#include "Player.h"
#include "UpdatableObject.h"

namespace engine2d {

    void Player::update(float dt) {
        if (!input) return;

        float dx = 0, dy = 0;
        if (input->isKeyDown(sf::Keyboard::W)) dy -= 1;
        if (input->isKeyDown(sf::Keyboard::S)) dy += 1;
        if (input->isKeyDown(sf::Keyboard::A)) dx -= 1;
        if (input->isKeyDown(sf::Keyboard::D)) dx += 1;

        if (dx != 0 || dy != 0) {
            translate(dx * speed * dt, dy * speed * dt);
            animate(dt);
        }
    }

} // namespace engine2d
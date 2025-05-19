#include "GAME/Units/Swordsman.hpp"
#include <stdexcept>

namespace sw::game {

Swordsman::Swordsman(const std::string& id, int x, int y, int health, int strength)
    : Unit(id, "Swordsman", x, y, health)
    , strength_(strength) {
    if (strength <= 0) {
        throw std::invalid_argument("Swordsman strength must be positive");
    }
}

// IMovable interface implementation
void Swordsman::moveTo(int x, int y) {
    setPosition(x, y);
}

int Swordsman::getX() const {
    return Unit::getX();
}

int Swordsman::getY() const {
    return Unit::getY();
}

// ICombatant interface implementation
int Swordsman::getHP() const {
    return Unit::getHealth();
}

void Swordsman::takeDamage(int damage) {
    Unit::takeDamage(damage);
}

bool Swordsman::isAlive() const {
    return Unit::isAlive();
}

int Swordsman::getStrength() const {
    return strength_;
}

} // namespace sw::game 
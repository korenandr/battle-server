#include "GAME/Units/Hunter.hpp"
#include <stdexcept>
#include <cmath>

namespace sw::game {

Hunter::Hunter(const std::string& id, int x, int y, int health, int agility, int strength, int range)
    : Unit(id, "Hunter", x, y, health)
    , agility_(agility)
    , strength_(strength)
    , range_(range) {
    if (agility <= 0) {
        throw std::invalid_argument("Hunter agility must be positive");
    }
    if (strength <= 0) {
        throw std::invalid_argument("Hunter strength must be positive");
    }
    if (range <= 0) {
        throw std::invalid_argument("Hunter range must be positive");
    }
}

// IMovable interface implementation
void Hunter::moveTo(int x, int y) {
    setPosition(x, y);
}

int Hunter::getX() const {
    return Unit::getX();
}

int Hunter::getY() const {
    return Unit::getY();
}

// ICombatant interface implementation
int Hunter::getHP() const {
    return Unit::getHealth();
}

void Hunter::takeDamage(int damage) {
    Unit::takeDamage(damage);
}

bool Hunter::isAlive() const {
    return Unit::isAlive();
}

int Hunter::getStrength() const {
    return strength_;
}

// IRanged interface implementation
bool Hunter::canShootAt(int x, int y) const {
    if (!isAlive()) {
        return false;
    }

    const int dx = std::abs(x - getX());
    const int dy = std::abs(y - getY());
    const int distance = std::max(dx, dy);

    return distance <= getRange();
}

int Hunter::getRange() const {
    return range_;
}

int Hunter::getAgility() const {
    return agility_;
}

} // namespace sw::game 
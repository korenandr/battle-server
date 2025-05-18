#include "GAME/Units/Unit.hpp"
#include <stdexcept>

namespace sw::game {

Unit::Unit(const std::string& id, const std::string& type, int x, int y, int health)
    : id_(id)
    , type_(type)
    , x_(x)
    , y_(y)
    , health_(health) {
    if (id.empty()) {
        throw std::invalid_argument("Unit ID cannot be empty");
    }
    if (type.empty()) {
        throw std::invalid_argument("Unit type cannot be empty");
    }
    if (health <= 0) {
        throw std::invalid_argument("Unit health must be positive");
    }
}

std::string Unit::getId() const {
    return id_;
}

std::string Unit::getType() const {
    return type_;
}

int Unit::getX() const {
    return x_;
}

int Unit::getY() const {
    return y_;
}

int Unit::getHealth() const {
    return health_;
}

void Unit::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Unit::setHealth(int health) {
    if (health <= 0) {
        throw std::invalid_argument("Unit health must be positive");
    }
    health_ = health;
}

void Unit::takeDamage(int damage) {
    if (damage < 0) {
        throw std::invalid_argument("Damage cannot be negative");
    }
    health_ = std::max(0, health_ - damage);
}

bool Unit::isAlive() const {
    return health_ > 0;
}

} // namespace sw::game 
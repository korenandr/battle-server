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

} // namespace sw::game 
#include "GAME/Units/Swordsman.hpp"

namespace sw::game {

Swordsman::Swordsman(const std::string& id, int x, int y, int health, int strength)
    : Unit(id, "Swordsman", x, y, health)
    , strength_(strength) {
}

} // namespace sw::game 
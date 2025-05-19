#include "GAME/Units/Hunter.hpp"
#include <stdexcept>

namespace sw::game {

Hunter::Hunter(const std::string& id, int x, int y, int health, int strength, int agility, int range)
    : Unit(id, "Hunter", x, y, health)
    , strength_(strength)
    , agility_(agility)
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

} // namespace sw::game 
#include "GAME/Units/Hunter.hpp"

namespace sw::game {

Hunter::Hunter(const std::string& id, int x, int y, int health, int agility, int strength, int range)
    : Unit(id, "Hunter", x, y, health)
    , agility_(agility)
    , strength_(strength)
    , range_(range) {
}

} // namespace sw::game 
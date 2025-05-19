#include "GAME/Units/UnitFactory.hpp"
#include "GAME/Units/Swordsman.hpp"
#include "GAME/Units/Hunter.hpp"
#include <stdexcept>

namespace sw::game {

std::shared_ptr<Unit> UnitFactory::createUnit(
    const std::string& type,
    const std::string& id,
    int x,
    int y,
    int health,
    int strength,
    int agility,
    int range
) {
    if (type == "Swordsman") {
        return std::make_shared<Swordsman>(id, x, y, health, strength);
    }
    else if (type == "Hunter") {
        return std::make_shared<Hunter>(id, x, y, health, agility, strength, range);
    }
    else {
        throw std::invalid_argument("Unknown unit type: " + type);
    }
}

} // namespace sw::game 
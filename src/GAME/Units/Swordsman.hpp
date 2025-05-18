#pragma once

#include "GAME/Units/Unit.hpp"

namespace sw::game {

class Swordsman : public Unit {
public:
    Swordsman(const std::string& id, int x, int y, int health, int strength);
    
    int getStrength() const { return strength_; }
    int getAgility() const { return 0; }  // Swordsmen have no agility
    int getRange() const { return 1; }    // Swordsmen have melee range

private:
    int strength_;
};

} // namespace sw::game 
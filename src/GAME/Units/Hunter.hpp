#pragma once

#include "GAME/Units/Unit.hpp"

namespace sw::game {

class Hunter : public Unit {
public:
    Hunter(const std::string& id, int x, int y, int health, int agility, int strength, int range);
    
    int getStrength() const { return strength_; }
    int getAgility() const { return agility_; }
    int getRange() const { return range_; }

private:
    int agility_;
    int strength_;
    int range_;
};

} // namespace sw::game 
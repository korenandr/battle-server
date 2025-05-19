#pragma once

#include "GAME/Units/Unit.hpp"
#include "GAME/Units/Mixins/MovableMixin.hpp"
#include "GAME/Units/Mixins/CombatantMixin.hpp"

namespace sw::game {

struct Swordsman : public Unit,
                   public MovableMixin<Swordsman>,
                   public CombatantMixin<Swordsman> {
public:
    Swordsman(const std::string& id, int x, int y, int health, int strength);
    
    int strength_ = 0;
};

} // namespace sw::game 
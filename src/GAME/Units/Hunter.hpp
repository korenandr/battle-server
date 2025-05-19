#pragma once

#include "GAME/Units/Unit.hpp"
#include "GAME/Units/Mixins/MovableMixin.hpp"
#include "GAME/Units/Mixins/CombatantMixin.hpp"
#include "GAME/Units/Mixins/RangedMixin.hpp"

namespace sw::game {

struct Hunter : public Unit,
                public MovableMixin<Hunter>,
                public CombatantMixin<Hunter>,
                public RangedMixin<Hunter> {
public:
    Hunter(const std::string& id, int x, int y, int health, int strength, int agility, int range);

    int strength_ = 0;
    int agility_ = 0;
    int range_ = 0;
};

} // namespace sw::game 
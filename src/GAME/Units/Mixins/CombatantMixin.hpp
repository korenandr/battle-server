#pragma once

#include "GAME/Units/Interfaces/ICombatant.hpp"
#include "GAME/Units/Unit.hpp"

#include <stdexcept>

namespace sw::game {

template<typename Derived>
class CombatantMixin : public ICombatant {
public:
    void takeDamage(int damage) override {
        if (damage < 0) {
            throw std::invalid_argument("Damage cannot be negative");
        }
        const auto health = static_cast<Derived*>(this)->Unit::getHealth();
        static_cast<Derived*>(this)->Unit::setHealth(std::max(0, health - damage));
    }

    int getStrength() const override {
        return static_cast<const Derived*>(this)->strength_;
    }
};

} // namespace sw::game 
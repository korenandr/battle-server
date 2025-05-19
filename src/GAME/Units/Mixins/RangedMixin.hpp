#pragma once

#include "GAME/Units/Interfaces/IRanged.hpp"
#include "GAME/Units/Unit.hpp"
#include <cmath>

namespace sw::game {

template<typename Derived>
class RangedMixin : public IRanged {
public:
    int getRange() const override {
        return static_cast<const Derived*>(this)->range_;
    }

    int getAgility() const override {
        return static_cast<const Derived*>(this)->agility_;
    }

    bool canShootAt(int x, int y) const override {
        // Calculate distance using Manhattan distance
        int dx = std::abs(x - static_cast<const Derived*>(this)->Unit::getX());
        int dy = std::abs(y - static_cast<const Derived*>(this)->Unit::getY());
        return (dx + dy) <= getRange();
    }
};

} // namespace sw::game 
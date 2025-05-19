#pragma once

#include "GAME/Units/Unit.hpp"
#include <memory>
#include <string>

namespace sw::game {

class UnitFactory {
public:
    // Factory method to create a unit
    static std::shared_ptr<Unit> createUnit(
        const std::string& type,
        const std::string& id,
        int x,
        int y,
        int health,
        int strength = 0,
        int agility = 0,
        int range = 0
    );

private:
    // Prevent instantiation
    UnitFactory() = default;
};

} // namespace sw::game 
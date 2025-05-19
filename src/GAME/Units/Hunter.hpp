#pragma once

#include "GAME/Units/Unit.hpp"
#include "GAME/Units/Interfaces/IMovable.hpp"
#include "GAME/Units/Interfaces/ICombatant.hpp"
#include "GAME/Units/Interfaces/IRanged.hpp"

namespace sw::game {

class Hunter : public Unit,
               public IMovable,
               public ICombatant,
               public IRanged {
public:
    Hunter(const std::string& id, int x, int y, int health, int agility, int strength, int range);
    
    // IMovable interface
    void moveTo(int x, int y) override;
    int getX() const override;
    int getY() const override;

    // ICombatant interface
    int getHP() const override;
    void takeDamage(int damage) override;
    bool isAlive() const override;
    int getStrength() const override;

    // IRanged interface
    bool canShootAt(int x, int y) const override;
    int getRange() const override;
    int getAgility() const override;

private:
    int agility_;
    int strength_;
    int range_;
};

} // namespace sw::game 
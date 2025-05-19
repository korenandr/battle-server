#pragma once

#include "GAME/Units/Unit.hpp"
#include "GAME/Units/Interfaces/IMovable.hpp"
#include "GAME/Units/Interfaces/ICombatant.hpp"

namespace sw::game {

class Swordsman : public Unit,
                  public IMovable,
                  public ICombatant {
public:
    Swordsman(const std::string& id, int x, int y, int health, int strength);
    
    // IMovable interface
    void moveTo(int x, int y) override;
    int getX() const override;
    int getY() const override;

    // ICombatant interface
    int getHP() const override;
    void takeDamage(int damage) override;
    bool isAlive() const override;
    int getStrength() const override;

private:
    int strength_;
};

} // namespace sw::game 
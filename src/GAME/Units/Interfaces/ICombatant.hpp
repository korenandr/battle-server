#pragma once

namespace sw::game {

class ICombatant {
public:
    virtual ~ICombatant() = default;
    
    virtual void takeDamage(int damage) = 0;
    virtual int getStrength() const = 0;
};

} // namespace sw::game
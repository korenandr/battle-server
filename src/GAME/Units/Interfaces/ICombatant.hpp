#pragma once

namespace sw::game {

class ICombatant {
public:
    virtual ~ICombatant() = default;
    
    // Health and damage methods
    virtual int getHP() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual bool isAlive() const = 0;
    
    // Combat attributes
    virtual int getStrength() const = 0;
};

} // namespace sw::game
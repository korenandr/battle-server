#pragma once

namespace sw::game {

class IRanged {
public:
    virtual ~IRanged() = default;
    
    // Ranged combat methods
    virtual bool canShootAt(int x, int y) const = 0;
    virtual int getRange() const = 0;
    virtual int getAgility() const = 0;
};

} // namespace sw::game
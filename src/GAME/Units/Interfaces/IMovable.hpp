#pragma once

namespace sw::game {

class IMovable {
public:
    virtual ~IMovable() = default;
    
    // Movement methods
    virtual void moveTo(int x, int y) = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
};

} // namespace sw::game
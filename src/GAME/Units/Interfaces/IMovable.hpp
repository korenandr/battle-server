#pragma once

namespace sw::game {

class IMovable {
public:
    virtual ~IMovable() = default;
    
    virtual void moveTo(int x, int y) = 0;
};

} // namespace sw::game
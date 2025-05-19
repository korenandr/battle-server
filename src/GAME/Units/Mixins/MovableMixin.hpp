#pragma once

#include "GAME/Units/Interfaces/IMovable.hpp"
#include "GAME/Units/Unit.hpp"

namespace sw::game {

template<typename Derived>
class MovableMixin : public IMovable {
public:
    void moveTo(int x, int y) override {
        static_cast<Derived*>(this)->setPosition(x, y);
    }
};

} // namespace sw::game 
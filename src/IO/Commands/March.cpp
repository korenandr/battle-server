#include "IO/Commands/March.hpp"
#include "GAME/MVC/Controller.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/UnitMoved.hpp"

namespace sw::io {

void March::execute(const std::shared_ptr<game::Controller>& controller) {
    if (!controller) {
        throw std::runtime_error("Controller is null");
    }

    auto unit = controller->getModel()->getUnit(std::to_string(unitId));
    if (!unit) {
        throw std::runtime_error("Unit not found: " + std::to_string(unitId));
    }

    // Log march start
    controller->getEventLog()->log(1, MarchStarted{
        unitId,
        static_cast<uint32_t>(unit->getX()),
        static_cast<uint32_t>(unit->getY()),
        targetX,
        targetY
    });

    // Move unit one step at a time until reaching target
    int currentX = unit->getX();
    int currentY = unit->getY();
    const int targetX = this->targetX;
    const int targetY = this->targetY;

    while (currentX != targetX || currentY != targetY) {
        // Calculate next step
        if (currentX < targetX) currentX++;
        else if (currentX > targetX) currentX--;
        
        if (currentY < targetY) currentY++;
        else if (currentY > targetY) currentY--;

        // Move unit
        unit->setPosition(currentX, currentY);
        
        // Log movement
        controller->getEventLog()->log(1, UnitMoved{
            unitId,
            static_cast<uint32_t>(currentX),
            static_cast<uint32_t>(currentY)
        });
    }

    // Log march end
    controller->getEventLog()->log(1, MarchEnded{
        unitId,
        static_cast<uint32_t>(currentX),
        static_cast<uint32_t>(currentY)
    });
}

} // namespace sw::io 
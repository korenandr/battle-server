#include "IO/Commands/SpawnHunter.hpp"
#include "GAME/MVC/Controller.hpp"
#include "GAME/Units/Hunter.hpp"
#include "IO/Events/UnitSpawned.hpp"

namespace sw::io {

void SpawnHunter::execute(const std::shared_ptr<game::Controller>& controller) {
    if (!controller) {
        throw std::runtime_error("Controller is null");
    }

    try {
        // Create a new Hunter with the command parameters
        auto hunter = std::make_shared<game::Hunter>(
            std::to_string(unitId),
            x,
            y,
            hp,
            strength,
            agility,
            range
        );

        // Add the Hunter to the model
        controller->getModel()->addUnit(hunter);

        // Log the Hunter spawn
        controller->getEventLog()->log(1, UnitSpawned{
            unitId,
            hunter->getType(),
            static_cast<uint32_t>(x),
            static_cast<uint32_t>(y)
        });

        /*
        controller->getView()->displayMessage("Hunter spawned successfully");
        controller->getView()->displayMap();
        */
    }
    catch (const std::exception& e) {
        controller->getView()->displayMessage(std::string("Failed to spawn Hunter: ") + e.what());
    }
}

} // namespace sw::io 
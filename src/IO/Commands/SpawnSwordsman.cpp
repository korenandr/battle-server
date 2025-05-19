#include "IO/Commands/SpawnSwordsman.hpp"
#include "GAME/MVC/Controller.hpp"
#include "GAME/Units/Swordsman.hpp"
#include "IO/Events/UnitSpawned.hpp"

namespace sw::io {

void SpawnSwordsman::execute(const std::shared_ptr<game::Controller>& controller) {
    if (!controller) {
        throw std::runtime_error("Controller is null");
    }

    try {
        // Create a new Swordsman with the command parameters
        auto swordsman = std::make_shared<game::Swordsman>(
            std::to_string(unitId),
            x,
            y,
            hp,
            strength
        );

        // Add the Swordsman to the model
        controller->getModel()->addUnit(swordsman);

        // Log the Swordsman spawn
        controller->getEventLog()->log(1, UnitSpawned{
            unitId,
            swordsman->getType(),
            static_cast<uint32_t>(x),
            static_cast<uint32_t>(y)
        });

        /*
        controller->getView()->displayMessage("Swordsman spawned successfully");
        controller->getView()->displayMap();
        */
    }
    catch (const std::exception& e) {
        controller->getView()->displayMessage(std::string("Failed to spawn Swordsman: ") + e.what());
    }
}

} // namespace sw::io 
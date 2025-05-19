#include "IO/Commands/CreateMap.hpp"
#include "GAME/MVC/Controller.hpp"
#include "IO/Events/MapCreated.hpp"

namespace sw::io {

void CreateMap::execute(const std::shared_ptr<game::Controller>& controller) {
    if (!controller) {
        throw std::runtime_error("Controller is null");
    }
    
    controller->getModel()->setMapSize(width, height);
    
    // Log map creation
    controller->getEventLog()->log(1, MapCreated{
        width,
        height
    });
    
    /*
    controller->getView()->displayMessage("Map created successfully");
    controller->getView()->displayMap();
    */
}

} // namespace sw::io 
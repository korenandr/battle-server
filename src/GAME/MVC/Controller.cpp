#include "GAME/MVC/Controller.hpp"
#include <stdexcept>

namespace sw::game {

Controller::Controller(
    const std::shared_ptr<game::Model>& model,
    const std::shared_ptr<game::View>& view,
    const std::shared_ptr<EventLog>& eventLog)
    : model_(model)
    , view_(view)
    , eventLog_(eventLog) {
    if (!model_) {
        throw std::invalid_argument("Model cannot be null");
    }
    if (!view_) {
        throw std::invalid_argument("View cannot be null");
    }
    if (!eventLog_) {
        throw std::invalid_argument("EventLog cannot be null");
    }
}

void Controller::handleCommand(const std::shared_ptr<io::Command>& command) {
    if (!command) {
        throw std::invalid_argument("Command cannot be null");
    }
    command->execute(shared_from_this());
}

} // namespace sw::game 
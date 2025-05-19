#pragma once

#include "GAME/MVC/Model.hpp"
#include "GAME/MVC/View.hpp"
#include "IO/Commands/Command.hpp"
#include "IO/System/EventLog.hpp"

#include <memory>

namespace sw::game {

class Controller : public std::enable_shared_from_this<Controller> {
public:
    Controller(const std::shared_ptr<game::Model>& model, 
               const std::shared_ptr<game::View>& view,
               const std::shared_ptr<EventLog>& eventLog);

    // Generic command handler
    void handleCommand(const std::shared_ptr<io::Command>& command);

    // Getters for components
    std::shared_ptr<Model> getModel() const { return model_; }
    std::shared_ptr<View> getView() const { return view_; }
    std::shared_ptr<EventLog> getEventLog() const { return eventLog_; }

private:
    std::shared_ptr<game::Model> model_;
    std::shared_ptr<game::View> view_;
    std::shared_ptr<EventLog> eventLog_;
};

} // namespace sw::game 
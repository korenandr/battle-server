#pragma once

#include "GAME/Model.hpp"
#include "GAME/View.hpp"
#include "IO/Commands/CreateMap.hpp"
#include "IO/Commands/SpawnSwordsman.hpp"
#include "IO/Commands/SpawnHunter.hpp"
#include "IO/Commands/March.hpp"
#include "IO/Events/MapCreated.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/UnitMoved.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/System/EventLog.hpp"

#include <memory>

namespace sw::game {

class Controller {
public:
    Controller(const std::shared_ptr<game::Model>& model, 
               const std::shared_ptr<game::View>& view,
               const std::shared_ptr<EventLog>& eventLog);

    // Command handlers
    void handleCreateMap(const io::CreateMap& command);
    void handleSpawnSwordsman(const io::SpawnSwordsman& command);
    void handleSpawnHunter(const io::SpawnHunter& command);
    void handleMarch(const io::March& command);

private:
    std::shared_ptr<game::Model> model_;
    std::shared_ptr<game::View> view_;
    std::shared_ptr<EventLog> eventLog_;
};

} // namespace sw::game 
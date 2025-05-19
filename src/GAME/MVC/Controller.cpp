#include "GAME/MVC/Controller.hpp"
#include "GAME/Units/Swordsman.hpp"
#include "GAME/Units/Hunter.hpp"
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

void Controller::handleCreateMap(const io::CreateMap& command) {
    model_->setMapSize(command.width, command.height);
    
    // Log map creation
    eventLog_->log(1, io::MapCreated{
        command.width,
        command.height
    });
    
    view_->displayMessage("Map created successfully");
    view_->displayMap();
}

void Controller::spawnUnit(const std::string& type,
                          const std::string& id,
                          int x,
                          int y,
                          int health,
                          int strength,
                          int agility,
                          int range) {
    try {
        auto unit = UnitFactory::createUnit(type, id, x, y, health, strength, agility, range);
        model_->addUnit(unit);
        
        // Log unit spawn
        eventLog_->log(1, io::UnitSpawned{
            static_cast<uint32_t>(std::stoi(id)),
            type,
            static_cast<uint32_t>(x),
            static_cast<uint32_t>(y)
        });
        
        view_->displayMessage("Unit spawned successfully");
        view_->displayMap();
    }
    catch (const std::exception& e) {
        view_->displayMessage(std::string("Failed to spawn unit: ") + e.what());
    }
}

void Controller::handleSpawnSwordsman(const io::SpawnSwordsman& command) {
    spawnUnit("Swordsman",
             std::to_string(command.unitId),
             command.x,
             command.y,
             command.hp,
             command.strength);
}

void Controller::handleSpawnHunter(const io::SpawnHunter& command) {
    spawnUnit("Hunter",
             std::to_string(command.unitId),
             command.x,
             command.y,
             command.hp,
             command.strength,
             command.agility,
             command.range);
}

void Controller::handleMarch(const io::March& command) {
    auto unit = model_->getUnit(std::to_string(command.unitId));
    if (!unit) {
        throw std::runtime_error("Unit not found: " + std::to_string(command.unitId));
    }

    // Log march start
    eventLog_->log(1, io::MarchStarted{
        command.unitId,
        static_cast<uint32_t>(unit->getX()),
        static_cast<uint32_t>(unit->getY()),
        command.targetX,
        command.targetY
    });

    // Move unit one step at a time until reaching target
    int currentX = unit->getX();
    int currentY = unit->getY();
    const int targetX = command.targetX;
    const int targetY = command.targetY;

    while (currentX != targetX || currentY != targetY) {
        // Calculate next step
        if (currentX < targetX) currentX++;
        else if (currentX > targetX) currentX--;
        
        if (currentY < targetY) currentY++;
        else if (currentY > targetY) currentY--;

        // Move unit
        unit->setPosition(currentX, currentY);
        
        // Log movement
        eventLog_->log(1, io::UnitMoved{
            command.unitId,
            static_cast<uint32_t>(currentX),
            static_cast<uint32_t>(currentY)
        });

        // Check for combat
        for (const auto& [otherUnitId, otherUnit] : model_->getAllUnits()) {
            if (otherUnitId != std::to_string(command.unitId) && 
                otherUnit->getX() == currentX && 
                otherUnit->getY() == currentY) {
                
                // Combat occurs
                int damage = unit->getStrength();
                otherUnit->takeDamage(damage);
                
                eventLog_->log(1, io::UnitAttacked{
                    command.unitId,
                    static_cast<uint32_t>(std::stoi(otherUnitId)),
                    static_cast<uint32_t>(damage),
                    static_cast<uint32_t>(otherUnit->getHealth())
                });

                if (!otherUnit->isAlive()) {
                    eventLog_->log(1, io::UnitDied{
                        static_cast<uint32_t>(std::stoi(otherUnitId))
                    });
                    model_->removeUnit(otherUnitId);
                }
            }
        }
    }

    // Log march end
    eventLog_->log(1, io::MarchEnded{
        command.unitId,
        static_cast<uint32_t>(currentX),
        static_cast<uint32_t>(currentY)
    });
}

} // namespace sw::game 
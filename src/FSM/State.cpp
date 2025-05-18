#include "State.hpp"
#include "Game.hpp"

#include <GAME/Controller.hpp>
#include <GAME/Model.hpp>
#include <GAME/View.hpp>

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>

#include <fstream>
#include <iostream>


namespace sw::fsm {

    // Implementations of state methods
    void SimulationInitState::enter(Game& game) {
        std::cout << "[SimulationInitState] Entering..." << std::endl;
    }
    void SimulationInitState::update(Game& game) {
        std::cout << "[SimulationInitState] Parsing commands..." << std::endl;

        // TODO: Make initialization here

        game.runSimulation();
    }
    void SimulationInitState::exit(Game& game) {
        std::cout << "[SimulationInitState] Exiting..." << std::endl;
    }

    void SimulationRunningState::enter(Game& game) {
        std::cout << "[SimulationRunningState] Simulation started." << std::endl;
    }
    void SimulationRunningState::update(Game& game) {
        std::cout << "[SimulationRunningState] Running turn..." << std::endl;

        // TODO: Run simulation here

        // Create model with a 10x10 map
        auto model = std::make_shared<game::Model>(10, 10);
        
        // Create view and controller
        auto view = std::make_shared<game::View>(model);
        auto eventLog = std::make_shared<EventLog>();
        auto controller = std::make_shared<game::Controller>(model, view, eventLog);

        // Set up command parser
        io::CommandParser parser;
        parser.add<io::CreateMap>([controller](auto command) { 
            controller->handleCreateMap(command); 
        })
        .add<io::SpawnSwordsman>([controller](auto command) { 
            controller->handleSpawnSwordsman(command); 
        })
        .add<io::SpawnHunter>([controller](auto command) { 
            controller->handleSpawnHunter(command); 
        })
        .add<io::March>([controller](auto command) { 
            controller->handleMarch(command); 
        });

        // Parse commands from file
        std::ifstream file("./commands_example.txt");
        parser.parse(file);

        game.endSimulation();
    }
    void SimulationRunningState::exit(Game& game) {
        std::cout << "[SimulationRunningState] Ending simulation." << std::endl;
    }

    void SimulationEndedState::enter(Game& game) {
        std::cout << "[SimulationEndedState] Simulation ended." << std::endl;
    }
    void SimulationEndedState::update(Game& game) {
        std::cout << "[SimulationEndedState] Awaiting restart..." << std::endl;

        // TODO: Make deinitialization here

        game.shutdown();
    }
    void SimulationEndedState::exit(Game& game) {
        std::cout << "[SimulationEndedState] Restarting..." << std::endl;
    }

} // namespace sw::fsm

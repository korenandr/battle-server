#include "State.hpp"
#include "Game.hpp"

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

#include <iostream>


namespace sw::fsm {

    bool IGameState::isProcessing() const {
        return _state == State::PROCESSING;
    }

    bool IGameState::isFinished() const {
        return _state == State::FINISHED;
    }

    bool IGameState::isFailed() const {
        return _state == State::FAILED;
    }

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

        io::CommandParser parser;
        parser.add<io::CreateMap>([](auto command) { printDebug(std::cout, command); })
            .add<io::SpawnSwordsman>([](auto command) { printDebug(std::cout, command); })
            .add<io::SpawnHunter>([](auto command) { printDebug(std::cout, command); })
            .add<io::March>([](auto command) { printDebug(std::cout, command); });

        //parser.parse(file);

        EventLog eventLog;

        eventLog.log(1, io::MapCreated{10, 10});
        eventLog.log(1, io::UnitSpawned{1, "Swordsman", 0, 0});
        eventLog.log(1, io::UnitSpawned{2, "Hunter", 9, 0});
        eventLog.log(1, io::MarchStarted{1, 0, 0, 9, 0});
        eventLog.log(1, io::MarchStarted{2, 9, 0, 0, 0});
        eventLog.log(1, io::UnitSpawned{3, "Swordsman", 0, 9});
        eventLog.log(1, io::MarchStarted{3, 0, 9, 0, 0});

        eventLog.log(2, io::UnitMoved{1, 1, 0});
        eventLog.log(2, io::UnitMoved{2, 8, 0});
        eventLog.log(2, io::UnitMoved{3, 0, 8});

        eventLog.log(3, io::UnitMoved{1, 2, 0});
        eventLog.log(3, io::UnitMoved{2, 7, 0});
        eventLog.log(3, io::UnitMoved{3, 0, 7});

        eventLog.log(4, io::UnitMoved{1, 3, 0});
        eventLog.log(4, io::UnitAttacked{2, 1, 5, 0});
        eventLog.log(4, io::UnitDied{1});
        eventLog.log(4, io::UnitMoved{3, 0, 6});

        eventLog.log(5, io::UnitMoved{2, 6, 0});
        eventLog.log(5, io::UnitMoved{3, 0, 5});

        eventLog.log(6, io::UnitMoved{2, 5, 0});
        eventLog.log(6, io::UnitMoved{3, 0, 4});

        eventLog.log(7, io::UnitAttacked{2, 3, 5, 5});
        eventLog.log(7, io::UnitMoved{3, 0, 3});

        eventLog.log(8, io::UnitAttacked{2, 3, 5, 0});
        eventLog.log(8, io::UnitDied{3});

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

}// sw::fsm

#include "State.hpp"

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
        std::cout << "[SimulationInitState] Waiting for map..." << std::endl;
    }
    void SimulationInitState::exit(Game& game) {
        std::cout << "[SimulationInitState] Exiting..." << std::endl;
    }

    void SimulationRunningState::enter(Game& game) {
        std::cout << "[SimulationRunningState] Simulation started." << std::endl;
    }
    void SimulationRunningState::update(Game& game) {
        std::cout << "[SimulationRunningState] Running turn..." << std::endl;
    }
    void SimulationRunningState::exit(Game& game) {
        std::cout << "[SimulationRunningState] Ending simulation." << std::endl;
    }

    void SimulationEndedState::enter(Game& game) {
        std::cout << "[SimulationEndedState] Simulation ended." << std::endl;
    }
    void SimulationEndedState::update(Game& game) {
        std::cout << "[SimulationEndedState] Awaiting restart..." << std::endl;
    }
    void SimulationEndedState::exit(Game& game) {
        std::cout << "[SimulationEndedState] Restarting..." << std::endl;
    }

}// sw::fsm

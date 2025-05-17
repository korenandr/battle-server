#include "Game.hpp"

#include <fstream>

namespace sw::fsm {

    Game::Game(int argc, char** argv) {
        if (argc != 2) {
            throw std::runtime_error("Error: No file specified in command line argument");
        }

        std::ifstream file(argv[1]);
        if (!file) {
            throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
        }

        initSimulation();
    }

    Game::~Game() {
        shutdown();
    }

    void Game::changeState(std::unique_ptr<IGameState>&& newState) {
        if (currentState) currentState->exit(*this);
        currentState = std::move(newState);
        if (currentState) currentState->enter(*this);
    }

    void Game::update() {
        if (currentState) currentState->update(*this);
    }

    std::string Game::getStateName() const {
        return currentState ? currentState->name() : "None";
    }

    void Game::initSimulation() {
        changeState(std::make_unique<SimulationInitState>());
    }

    void Game::runSimulation() {
        changeState(std::make_unique<SimulationRunningState>());
    }

    void Game::endSimulation() {
        changeState(std::make_unique<SimulationEndedState>());
    }

    void Game::shutdown() {
        changeState(nullptr);
    }

    int Game::run() {
        while(currentState) {
            update();
        }

        return 0;
    }

} // namespace sw::fsm

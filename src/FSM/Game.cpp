#include "Game.hpp"

namespace sw::fsm
{
    Game::Game() {
        initSimulation();
    }

    Game::~Game() {
        endSimulation();
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

} // namespace sw::fsm

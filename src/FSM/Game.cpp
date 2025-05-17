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

    void Game::nextState() {
        if (!currentState || currentState->isProcessing()) return;
        if (currentState->isFailed()) {
            shutdown();
            return;
        }
        if (!currentState->isFinished()) {
            throw "Unknown state of the game state";
        }

        if (currentState->name() == SimulationInitState::Name) {
            runSimulation();
        } else if(currentState->name() == SimulationRunningState::Name) {
            endSimulation();
        } else if(currentState->name() == SimulationEndedState::Name) {
            shutdown();
        } else {
            throw "Unknown state";
        }
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
            nextState();
        }

        return 0;
    }

} // namespace sw::fsm

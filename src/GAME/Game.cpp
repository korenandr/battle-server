#include "Game.hpp"

#include <GAME/MVC/Model.hpp>
#include <GAME/MVC/View.hpp>

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>

#include <fstream>

namespace {
    const int DEFAULT_MAP_WIDTH = 10;
    const int DEFAULT_MAP_HEIGHT = 10;
}

namespace sw::game {

Game::Game() {
    // Initialize MVC components
    auto model = std::make_shared<Model>(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
    auto view = std::make_shared<View>(model);
    auto eventLog = std::make_shared<EventLog>();
    controller_ = std::make_shared<Controller>(model, view, eventLog);
    
    setupCommandParser();
}

void Game::setupCommandParser() {
    // Set up command parser using the helper method
    addCommandHandler<io::CreateMap>();
    addCommandHandler<io::March>();
    addCommandHandler<io::SpawnSwordsman>();
    addCommandHandler<io::SpawnHunter>();
}

    int Game::run(int argc, char** argv) {
        if (argc != 2) {
            throw std::runtime_error("Error: No file specified in command line argument");
        }

        std::ifstream file(argv[1]);
        if (!file) {
            throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
        }

        // Parse commands from file
        parser_.parse(file);

        return 0;
    }

} // namespace sw::game

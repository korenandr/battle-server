#include "Game.hpp"

#include <GAME/MVC/Model.hpp>
#include <GAME/MVC/View.hpp>
#include <IO/Commands/Command.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/SpawnHunter.hpp>

#include <fstream>

namespace {
    const int DEFAULT_MAP_WIDTH = 10;
    const int DEFAULT_MAP_HEIGHT = 10;
}

namespace sw::game {

    Game::Game() {
        auto model = std::make_shared<game::Model>(DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
        
        // Create view and controller
        auto view = std::make_shared<game::View>(model);
        auto eventLog = std::make_shared<EventLog>();
        controller_ = std::make_shared<game::Controller>(model, view, eventLog);

        // Set up command parser
        parser_.add<io::CreateMap>([this](auto command) { 
            controller_->handleCommand(command); 
        })
        .add<io::March>([this](auto command) { 
            controller_->handleCommand(command); 
        })
        .add<io::SpawnSwordsman>([this](auto command) { 
            controller_->handleCommand(command); 
        })
        .add<io::SpawnHunter>([this](auto command) { 
            controller_->handleCommand(command); 
        });
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

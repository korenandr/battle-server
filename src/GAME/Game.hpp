#pragma once

#include "GAME/MVC/Controller.hpp"
#include "IO/System/CommandParser.hpp"
#include <memory>

namespace sw::game {

    class Game final {
        private:

            std::shared_ptr<game::Controller> controller_;
            io::CommandParser parser_;

            void setupCommandParser();
            template<typename T>
            void addCommandHandler() {
                parser_.add<T>([this](auto command) {
                    controller_->handleCommand(command);
                });
            }

        public:
            Game();

            int run(int argc, char** argv);
    };

} // namespace sw::game

#pragma once

#include <GAME/Controller.hpp>
#include <IO/System/CommandParser.hpp>

#include <memory>

namespace sw::game {

    class Game final {
        private:

            std::shared_ptr<game::Controller> controller_;
            io::CommandParser parser_;

        public:
            Game();

            int run(int argc, char** argv);
    };

} // namespace sw::game

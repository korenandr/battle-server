#include "State.hpp"

#include <memory>
#include <string>

namespace sw::fsm
{
    class Game {
        private:
            std::unique_ptr<IGameState> currentState;

        private:
            void changeState(std::unique_ptr<IGameState>&& newState);

            void update();

            void initSimulation();

            void endSimulation();

        public:
            Game();
            ~Game();

            Game(const Game&) = delete;
            
            Game(Game&& other) noexcept = default;
            
            Game& operator=(const Game&) = delete;
            
            Game& operator=(Game&& other) noexcept = default;

        public:
            std::string getStateName() const;

            void runSimulation();
    };

} // namespace sw::fsm

#include "State.hpp"

#include <memory>
#include <string>

namespace sw::fsm
{
    class Game final {
        friend SimulationInitState;
        friend SimulationRunningState;
        friend SimulationEndedState;

        private:
            std::unique_ptr<IGameState> currentState;

        private:
            void changeState(std::unique_ptr<IGameState>&& newState);

            void update();

            void initSimulation();

            void runSimulation();

            void endSimulation();

            void shutdown();

        public:
            explicit Game(int argc, char** argv);
            ~Game();

            Game(const Game&) = delete;
            
            Game(Game&& other) noexcept = default;
            
            Game& operator=(const Game&) = delete;
            
            Game& operator=(Game&& other) noexcept = default;

        public:
            std::string getStateName() const;

            int run();
    };

} // namespace sw::fsm

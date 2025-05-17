#pragma once

#include <string>

namespace sw::fsm
{
    class Game;

    class IGameState {

        enum class State {
            PROCESSING = 0,
            FINISHED = 1,
            FAILED = 2,
        };
    
    private:
        State _state;

    public:
        virtual ~IGameState() = default;

        virtual void enter(Game& game) = 0;
        virtual void update(Game& game) = 0;
        virtual void exit(Game& game) = 0;

        virtual std::string name() const = 0;
        
        bool isProcessing() const;
        bool isFinished() const;
        bool isFailed() const;
    };

    // States
    class SimulationInitState final : public IGameState {
    public:
        constexpr static const char* Name = "SimulationInit";
        
    public:
        void enter(Game& game) override;
        void update(Game& game) override;
        void exit(Game& game) override;

        std::string name() const override { return Name; }
    };

    class SimulationRunningState final : public IGameState {
    public:
        constexpr static const char* Name = "SimulationRunning";

    public:
        void enter(Game& game) override;
        void update(Game& game) override;
        void exit(Game& game) override;

        std::string name() const override { return Name; }
    };

    class SimulationEndedState final : public IGameState {
    public:
        constexpr static const char* Name = "SimulationEnded";

    public:
        void enter(Game& game) override;
        void update(Game& game) override;
        void exit(Game& game) override;

        std::string name() const override { return Name; }
    };

} // sw::fsm

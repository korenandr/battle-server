#pragma once
#include <memory>

namespace sw::game {
    class Controller;
}

namespace sw::io {

struct Command {
public:
    virtual ~Command() = default;
    virtual void execute(const std::shared_ptr<game::Controller>& controller) = 0;
};

} // namespace sw::io 
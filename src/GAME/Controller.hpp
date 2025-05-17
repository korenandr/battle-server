#pragma once

#include "GAME/Units/Unit.hpp"
#include <memory>
#include <string>

namespace sw::game {

class Model;
class View;

class Controller {
public:
    Controller(const std::shared_ptr<Model>& model, const std::shared_ptr<View>& view);

    // Unit management
    void addUnit(const std::shared_ptr<Unit>& unit);
    void removeUnit(const std::string& unitId);
    void moveUnit(const std::string& unitId, int newX, int newY);

    // Display methods
    void displayGameState() const;
    void displayUnit(const std::string& unitId) const;

private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<View> view_;
};

} // namespace sw::game
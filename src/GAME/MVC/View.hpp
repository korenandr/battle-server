#pragma once

#include <memory>
#include <string>
#include "Model.hpp"

namespace sw::game {

class View {
public:
    explicit View(const std::shared_ptr<Model>& model);

    // Display methods
    void displayMap() const;
    void displayUnit(const std::string& unitId) const;
    void displayAllUnits() const;
    void displayMessage(const std::string& message) const;

private:
    std::shared_ptr<Model> model_;
    void displayUnitAtPosition(int x, int y) const;
};

} // namespace sw::game 
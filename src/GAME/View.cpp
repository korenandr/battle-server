#include "View.hpp"

#include <iostream>
#include <iomanip>

namespace sw::game {

View::View(const std::shared_ptr<Model>& model) : model_(model) {
    if (!model_) {
        throw std::invalid_argument("Model cannot be null");
    }
}

void View::displayMap() const {
    const int width = model_->getMapWidth();
    const int height = model_->getMapHeight();

    // Print top border
    std::cout << std::string(width * 2 + 3, '-') << '\n';

    // Print map content
    for (int y = 0; y < height; ++y) {
        std::cout << "| ";
        for (int x = 0; x < width; ++x) {
            displayUnitAtPosition(x, y);
            std::cout << ' ';
        }
        std::cout << "|\n";
    }

    // Print bottom border
    std::cout << std::string(width * 2 + 3, '-') << '\n';
}

void View::displayUnit(const std::string& unitId) const {
    const auto unit = model_->getUnit(unitId);
    if (unit) {
        std::cout << "Unit " << unitId << ":\n"
                  << "  Type: " << unit->getType() << '\n'
                  << "  Position: (" << unit->getX() << ", " << unit->getY() << ")\n"
                  << "  Health: " << unit->getHealth() << '\n';
    } else {
        std::cout << "Unit " << unitId << " not found\n";
    }
}

void View::displayAllUnits() const {
    const auto& units = model_->getAllUnits();
    if (units.empty()) {
        std::cout << "No units on the map\n";
        return;
    }

    std::cout << "Units on the map:\n";
    for (const auto& unit : units) {
        displayUnit(unit->getId());
    }
}

void View::displayMessage(const std::string& message) const {
    std::cout << message << '\n';
}

void View::displayUnitAtPosition(int x, int y) const {
    const auto& units = model_->getAllUnits();
    for (const auto& unit : units) {
        if (unit->getX() == x && unit->getY() == y) {
            std::cout << unit->getType()[0];  // Display first letter of unit type
            return;
        }
    }
    std::cout << '.';  // Empty space
}

} // namespace sw::game 
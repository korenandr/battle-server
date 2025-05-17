#include "Controller.hpp"
#include "Model.hpp"
#include "View.hpp"

#include <stdexcept>

namespace sw::game {

Controller::Controller(const std::shared_ptr<Model>& model, const std::shared_ptr<View>& view)
    : model_(model), view_(view) {
    if (!model_) {
        throw std::invalid_argument("Model cannot be null");
    }
    if (!view_) {
        throw std::invalid_argument("View cannot be null");
    }
}

void Controller::addUnit(const std::shared_ptr<Unit>& unit) {
    try {
        model_->addUnit(unit);
        view_->displayMessage("Unit added successfully");
    } catch (const std::exception& e) {
        view_->displayMessage(std::string("Failed to add unit: ") + e.what());
    }
}

void Controller::removeUnit(const std::string& unitId) {
    try {
        model_->removeUnit(unitId);
        view_->displayMessage("Unit removed successfully");
    } catch (const std::exception& e) {
        view_->displayMessage(std::string("Failed to remove unit: ") + e.what());
    }
}

void Controller::moveUnit(const std::string& unitId, int newX, int newY) {
    try {
        auto unit = model_->getUnit(unitId);
        if (!unit) {
            throw std::runtime_error("Unit not found");
        }

        if (!model_->isPositionValid(newX, newY)) {
            throw std::out_of_range("New position is out of map bounds");
        }

        if (model_->isPositionOccupied(newX, newY)) {
            throw std::runtime_error("New position is already occupied");
        }

        unit->setPosition(newX, newY);
        view_->displayMessage("Unit moved successfully");
    } catch (const std::exception& e) {
        view_->displayMessage(std::string("Failed to move unit: ") + e.what());
    }
}

void Controller::displayGameState() const {
    view_->displayMap();
    view_->displayAllUnits();
}

void Controller::displayUnit(const std::string& unitId) const {
    view_->displayUnit(unitId);
}

} // namespace sw::game 
#include "Model.hpp"

#include <algorithm>
#include <stdexcept>

namespace sw::game {

Model::Model(int width, int height) : mapWidth_(width), mapHeight_(height) {
    if ((width <= 0) || (height <= 0)) {
        throw std::invalid_argument("Map dimensions must be positive");
    }
}

void Model::addUnit(std::shared_ptr<Unit> unit) {
    if (!unit) {
        throw std::invalid_argument("Unit cannot be null");
    }

    // Check if position is valid
    if ((unit->getX() < 0) || (unit->getX() >= mapWidth_) ||
        (unit->getY() < 0) || (unit->getY() >= mapHeight_)) {
        throw std::out_of_range("Unit position is out of map bounds");
    }

    // Check if position is already occupied
    for (const auto& existingUnit : units_) {
        if ((existingUnit->getX() == unit->getX()) && 
            (existingUnit->getY() == unit->getY())) {
            throw std::runtime_error("Position is already occupied");
        }
    }

    units_.push_back(unit);
}

void Model::removeUnit(const std::string& unitId) {
    units_.erase(
        std::remove_if(std::begin(units_), std::end(units_),
            [&unitId](const auto& unit) { return unit->getId() == unitId; }),
        std::end(units_)
    );
}

std::shared_ptr<Unit> Model::getUnit(const std::string& unitId) const {
    auto it = std::find_if(std::cbegin(units_), std::cend(units_),
        [&unitId](const auto& unit) { return unit->getId() == unitId; });
    
    return it != std::cend(units_) ? *it : nullptr;
}

const std::vector<std::shared_ptr<Unit>>& Model::getAllUnits() const {
    return units_;
}

int Model::getMapWidth() const {
    return mapWidth_;
}

int Model::getMapHeight() const {
    return mapHeight_;
}

bool Model::isPositionValid(int x, int y) const {
    return x >= 0 && x < mapWidth_ && y >= 0 && y < mapHeight_;
}

bool Model::isPositionOccupied(int x, int y) const {
    return std::any_of(std::cbegin(units_), std::cend(units_),
        [x, y](const auto& unit) {
            return unit->getX() == x && unit->getY() == y;
        });
}

} // namespace sw::game 
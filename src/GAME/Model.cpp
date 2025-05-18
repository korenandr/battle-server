#include "Model.hpp"

#include <algorithm>
#include <stdexcept>

namespace sw::game {

Model::Model(int width, int height) : mapWidth_(width), mapHeight_(height) {
    if ((width <= 0) || (height <= 0)) {
        throw std::invalid_argument("Map dimensions must be positive");
    }
}

void Model::setMapSize(int width, int height) {
    if ((width <= 0) || (height <= 0)) {
        throw std::invalid_argument("Map dimensions must be positive");
    }
    mapWidth_ = width;
    mapHeight_ = height;
}

void Model::addUnit(std::shared_ptr<Unit> unit) {
    if (!unit) {
        throw std::invalid_argument("Unit cannot be null");
    }

    if (!isPositionValid(unit->getX(), unit->getY())) {
        throw std::out_of_range("Unit position is out of map bounds");
    }

    if (isPositionOccupied(unit->getX(), unit->getY())) {
        throw std::runtime_error("Position is already occupied");
    }

    units_[unit->getId()] = unit;
}

void Model::removeUnit(const std::string& unitId) {
    units_.erase(unitId);
}

std::shared_ptr<Unit> Model::getUnit(const std::string& unitId) const {
    const auto it = units_.find(unitId);
    return it != units_.end() ? it->second : nullptr;
}

std::unordered_map<std::string, std::shared_ptr<Unit>> Model::getAllUnits() const {
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
            return unit.second->getX() == x && unit.second->getY() == y;
        });
}

} // namespace sw::game 
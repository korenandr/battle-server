#pragma once

#include "GAME/Units/Unit.hpp"

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace sw::game {

class Model {
public:
    Model(int width, int height);

    // Unit management
    void addUnit(std::shared_ptr<Unit> unit);
    void removeUnit(const std::string& unitId);
    std::shared_ptr<Unit> getUnit(const std::string& unitId) const;
    const std::vector<std::shared_ptr<Unit>>& getAllUnits() const;

    // Map management
    void setMapSize(int width, int height);
    int getMapWidth() const;
    int getMapHeight() const;

    // Map validations
    bool isPositionValid(int x, int y) const;
    bool isPositionOccupied(int x, int y) const;

private:
    std::vector<std::shared_ptr<Unit>> units_;
    std::unordered_map<std::string, std::shared_ptr<Unit>> unitMap_;
    int mapWidth_ = 0;
    int mapHeight_ = 0;
};

} // namespace sw::game 
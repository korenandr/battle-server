#pragma once

#include <string>

namespace sw::game {

class Unit {
public:
    Unit(const std::string& id, const std::string& type, int x, int y, int health);

    // Getters
    std::string getId() const;
    std::string getType() const;
    int getX() const;
    int getY() const;
    int getHealth() const;

    // Setters
    void setPosition(int x, int y);
    void setHealth(int health);
    void takeDamage(int damage);

    // State
    bool isAlive() const;

private:
    std::string id_;
    std::string type_;
    int x_;
    int y_;
    int health_;
};

} // namespace sw::game 
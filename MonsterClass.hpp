//
// Created by Scooter on 5/31/2024.
//

#ifndef CSFINAL_MONSTERCLASS_HPP
#define CSFINAL_MONSTERCLASS_HPP

#include <iostream>

class Monster {
private:
    std::string color;
    std::string type;
    int armor;
    int health;
    int gold;
public:
    Monster() : color(""), type(""), armor(0), health(0), gold(0){};
    Monster(const std::string& color, const std::string& type, int armor, int health, int gold)
    : color(color), type(type), armor(armor), health(health), gold(gold) {};

    ~Monster() {};

    std::string getColor() const {
        return color;
    }
    std::string getType() const{
        return type;
    }
    int getArmor() const {
        return armor;
    }
    int getHealth() const {
        return health;
    }
    int getGold() const {
        return gold;
    }

    void setColor(const std::string& setColor){
        this->color = setColor;
    }
    void setType(const std::string& setType){
        this->type = setType;
    }
    void setArmor(const int& setArmor){
        this->armor = setArmor;
    }

    void setHealth(const int& setHealth){
        this->health = setHealth;
    }
    void setGold(const int& setGold){
        this->gold = setGold;
    }



};

#endif //CSFINAL_MONSTERCLASS_HPP

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
        return this->color;
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
class Player{
private:
    std::string name;
    int armor;
    int damage;
    int maxHealth;
    int currentHealth;
    int playerGold;
public:
    Player() : name(""), armor(5), damage(5), maxHealth(3), currentHealth(3), playerGold(0){};
    Player(const std::string& name, int armor, int damage, int maxHealth, int currentHealth, int playerGold)
    : name(name), armor(armor), damage(damage), maxHealth(maxHealth), currentHealth(currentHealth), playerGold(playerGold){};
    ~Player() {};
    // getters
    std::string getName() const {
        return this->name;
    }
    int getArmor() const {
        return this->armor;
    }
    int getDamage() const {
        return this->damage;
    }
    int getCurrentHealth() const {
        return this->currentHealth;
    }
    int getMaxHealth() const {
        return this->maxHealth;
    }
    int getGold() const {
        return this->playerGold;
    }

    //setters
    void setName(const std::string& charName){
        this->name = charName;
    }
    void setArmor(int setArmor){
        this->armor = setArmor;
    }
    void setDamage(int setDamage){
        this->damage = setDamage;
    }
    void setMaxHealth(int setMax){
        this->maxHealth = setMax;
    }
    void setCurrentHealth(int setCurrent){
        this->currentHealth = setCurrent;
    }
    void setGold(int setGold){
        this->playerGold = setGold;
    }





};

#endif //CSFINAL_MONSTERCLASS_HPP

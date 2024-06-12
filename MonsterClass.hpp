//
// Created by Scooter on 5/31/2024.
//

#ifndef CSFINAL_MONSTERCLASS_HPP
#define CSFINAL_MONSTERCLASS_HPP

#include <iostream>
#include "RandomGeneration.hpp"


// ANSI colors

extern const char* RESET;
extern const char* BLACK;
extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* MAGENTA;
extern const char* CYAN;
extern const char* WHITE;

extern const char* BRIGHT_BLACK;
extern const char* BRIGHT_GREEN;
extern const char* BRIGHT_WHITE;
extern const char* BRIGHT_YELLOW;
extern const char* BRIGHT_BLUE;
extern const char* BRIGHT_MAGENTA;
extern const char* BRIGHT_CYAN;
extern const char* BRIGHT_RED;

class Monster {
private:
    std::string color;
    std::string type;
    std::string action;
    char letter;
    int health;
    int damage;
public:
    Monster() : color(""), type(""), action(""), letter('M'), health(0), damage(0){};
    Monster(const std::string& color, const std::string& type, const std::string& action, const char& letter, int health, int damage)
    : color(color), type(type), action(action), letter(letter), health(health), damage(damage) {};

    virtual ~Monster() {};

    virtual std::string getColor() const { return this->color; }
    virtual std::string getType() const { return this->type; }
    virtual std::string getAction() const { return this->action; }
    virtual char getLetter() const { return this->letter; }
    virtual int getHealth() const { return this->health; }
    virtual int getDamage() const { return this->damage; }

    void setColor(const std::string& setColor) { this->color = setColor; }
    void setType(const std::string& setType) { this->type = setType; }
    void setAction(const std::string& setAction) { this->action = setAction; }
    void setLetter(const char& setLetter) { this->letter = setLetter; }
    void setHealth(const int& setHealth) { this->health = setHealth; }
    void setDamage(const int& setDamage) { this->damage = setDamage; }

};

class Enemy : public Monster{
public:
    Enemy(const std::string& color, const std::string type, const std::string action, char letter, int health, int damage)
    : Monster(color, type, action, letter, health, damage){}

    virtual ~Enemy() = default;

};

class Skelly : public Enemy {
public:
    Skelly() : Enemy(BRIGHT_BLACK, "Skeleton", "You receive Amulet of Undeath!", 'S', 3, 1) {}
};

class Slime : public Enemy {
public:
    Slime() : Enemy(BRIGHT_GREEN, "Slime", "The slain Slime is beginning to explode!", 'L', 2, 0){}
};

class Ghost : public Enemy {
public:
    Ghost() : Enemy(BRIGHT_WHITE, "Ghost", "The slain ghost is attempting to rob you!", 'O', 1, 1) {}
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

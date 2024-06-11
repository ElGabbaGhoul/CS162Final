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

class Monster;

const int MONSTER_COUNT = 4;

extern Monster* monsters[MONSTER_COUNT];

class Monster {
private:
    // color = visual tell of type
    std::string color;
    // type = slime/skelly/ghost
    std::string type;
    std::string action;
    char letter;
    int armor;
    int health;
    int damage;
public:
    Monster() : color(""), type(""), action(""), letter('M'), armor(0), health(0), damage(0){};
    Monster(const std::string& color, const std::string& type, const std::string& action, const char& letter, int armor, int health, int damage)
    : color(color), type(type), action(action), letter(letter), armor(armor), health(health), damage(damage) {};

    virtual ~Monster() {};

    std::string getColor() const {
        return this->color;
    }
    std::string getType() const{
        return this->type;
    }
    std::string getAction() const {
        return this->action;
    }
    char getLetter() const{
        return this->letter;
    }
    int getArmor() const {
        return this->armor;
    }
    int getHealth() const {
        return this->health;
    }
    int getDamage() const {
        return this->damage;
    }


    void setColor(const std::string& setColor){
        this->color = setColor;
    }
    void setType(const std::string& setType){
        this->type = setType;
    }
    void setAction(const std::string& setAction){
        this->action = setAction;
    }
    void setLetter(const char& setLetter){
        this->letter = setLetter;
    }
    void setArmor(const int& setArmor){
        this->armor = setArmor;
    }
    void setHealth(const int& setHealth){
        this->health = setHealth;
    }
    void setDamage(const int& setDamage){
        this->damage = setDamage;
    }

};

class Enemy : public Monster{
public:
    Enemy(const std::string& color, const std::string type, const std::string action, char letter, int armor, int health, int damage)
    : Monster(color, type, action, letter, armor, health, damage){}

    virtual ~Enemy() = default;

    virtual std::string getEnemyColor() const = 0;
    virtual std::string getEnemyType() const = 0;
    virtual std::string getEnemyAction() const = 0;
    virtual char getEnemyLetter() const = 0;
    virtual int getEnemyArmor() const = 0;
    virtual int getEnemyHealth() const = 0;
    virtual int getEnemyDamage() const = 0;
};

class Skelly : public Enemy {
public:
    Skelly() : Enemy(BRIGHT_BLACK, "Skeleton", "You receive Amulet of Undeath!", 'S', 10, 3, 1) {}

    std::string getEnemyColor() const override {return this->getColor();}
    std::string getEnemyType() const override {return this->getType();}
    std::string getEnemyAction() const override {return this->getAction();}
    char getEnemyLetter() const override {return this->getLetter();}
    int getEnemyArmor() const override {return this->getArmor();}
    int getEnemyHealth() const override {return this->getHealth();}
    int getEnemyDamage() const override {return this->getDamage();}
};

class Slime : public Enemy {
public:
    Slime() : Enemy(BRIGHT_GREEN, "Slime", "The slain Slime is beginning to explode!", 'L', 5, 2, 0){}

    std::string getEnemyColor() const override {return this->getColor();}
    std::string getEnemyType() const override {return this->getType();}
    std::string getEnemyAction() const override {return this->getAction();}
    char getEnemyLetter() const override {return this->getLetter();}
    int getEnemyArmor() const override {return this->getArmor();}
    int getEnemyHealth() const override {return this->getHealth();}
    int getEnemyDamage() const override {return this->getDamage();}
};

class Ghost : public Enemy {
public:
    Ghost() : Enemy(BRIGHT_WHITE, "Ghost", "The slain ghost is attempting to rob you!", 'O', 1, 1, 1) {}


    std::string getEnemyColor() const override {return this->getColor();}
    std::string getEnemyType() const override {return this->getType();}
    std::string getEnemyAction() const override {return this->getAction();}
    char getEnemyLetter() const override {return this->getLetter();}
    int getEnemyArmor() const override {return this->getArmor();}
    int getEnemyHealth() const override {return this->getHealth();}
    int getEnemyDamage() const override {return this->getDamage();}
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

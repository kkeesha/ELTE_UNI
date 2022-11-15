#pragma once
#include <string>
#include "Day.h"

using namespace std;

class Animal{
protected:
    string _name;
    int _eLevel;
    Animal (const string &str, int e = 0) :_name(str), _eLevel(e) {}
public:
    string name() const { return _name; }
    int eLevel() const { return _eLevel; }
    bool alive() const { return _eLevel > 0; }
    void changeLevel(int e) { _eLevel += e; }
    virtual void takeCare(Day* &days) = 0;
    virtual ~Animal () {}
};

// Tarantula class
class Tarantula : public Animal {
        public:
    Tarantula(const string &str, int e = 0) : Animal(str, e){}
    void takeCare(Day* &days) override {
        days = days->takeCare(this);
    }
};

// Hamster class
class Hamster : public Animal {
public:
    Hamster(const string &str, int e = 0) : Animal(str, e){}
    void takeCare(Day* &days) override {
        days = days->takeCare(this);
    }
};

// Cat class
class Cat : public Animal {
public:
    Cat(const string &str, int e = 0) : Animal(str, e){}
    void takeCare(Day* &days) override{
        days = days->takeCare(this);
    }
};


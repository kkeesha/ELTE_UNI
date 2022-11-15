#pragma once

#include <string>

class Tarantula;
class Hamster;
class Cat;

// class of the abstract grounds
class Day{
public:
    virtual Day* takeCare(Tarantula *p) = 0;
    virtual Day* takeCare(Hamster *p) = 0;
    virtual Day* takeCare(Cat *p) = 0;
    virtual ~Day() {}
};

// class of usual day
class Usual : public Day
{
public:
    static Usual* instance();
    Day* takeCare(Tarantula *p) override;
    Day* takeCare(Hamster *p) override;
    Day* takeCare(Cat   *p) override;
    static void destroy() ;
protected:
    Usual(){}
private:
    static Usual* _instance;
};

// class of joyful day
class Joyful : public Day
{
public:
    static Joyful* instance();
    Day* takeCare(Tarantula *p) override;
    Day* takeCare(Hamster *p) override;
    Day* takeCare(Cat   *p) override;
    static void destroy() ;
protected:
    Joyful(){}
private:
    static Joyful* _instance;
};

// class of blue day
class Blue : public Day
{
public:
    static Blue* instance();
    Day* takeCare(Tarantula *p) override;
    Day* takeCare(Hamster *p) override;
    Day* takeCare(Cat   *p) override;
    static void destroy() ;
protected:
    Blue(){}
private:
    static Blue* _instance;
};

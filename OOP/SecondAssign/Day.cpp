#include "Day.h"
#include "Animal.h"

using namespace std;

// implementation of class Joyful
Joyful* Joyful::_instance = nullptr;
Joyful* Joyful::instance()
{
    if(_instance == nullptr) {
        _instance = new Joyful();
    }
    return _instance;
}
void Joyful::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

Day* Joyful::takeCare(Tarantula *p)
{

    p->changeLevel(1);
    return this;
}

Day* Joyful::takeCare(Hamster *p)
{
    p->changeLevel(2);
    return this;
}

Day* Joyful::takeCare(Cat *p)
{

    p->changeLevel(3);
    return this;
}

// implementation of class Usual
Usual* Usual::_instance = nullptr;
Usual* Usual::instance()
{
    if(_instance == nullptr) {
        _instance = new Usual();
    }
    return _instance;
}
void Usual::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

Day* Usual::takeCare(Tarantula *p)
{
    p->changeLevel(-2);
    return this;
}

Day* Usual::takeCare(Hamster *p)
{
    p->changeLevel(-3);
    return this;
}

Day* Usual::takeCare(Cat *p)
{
    p->changeLevel(3);
    return this;
}

// implementation of class Blue
Blue* Blue::_instance = nullptr;
Blue* Blue::instance()
{
    if(_instance == nullptr) {
        _instance = new Blue();
    }
    return _instance;
}
void Blue::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

Day* Blue::takeCare(Tarantula *p)
{
    p->changeLevel(-3);
    return this;
}

Day* Blue::takeCare(Hamster *p)
{
    p->changeLevel(-5);
    return this;
}

Day* Blue::takeCare(Cat *p)
{
    p->changeLevel(-7);
    return this;
}

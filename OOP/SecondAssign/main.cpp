//Alkozhoev Kairat - DMDDNY
//01.05.2022
//OOP - group 5
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Animal.h"
#include <string>

using namespace std;

void create(const string &str, vector<Animal*> &animals, vector<Day*> &day)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}

    int n; f >> n;
    animals.resize(n);
    for( int i=0; i<n; ++i ){
        char ch; string name; int level;
        f >> ch >> name >> level;
        switch(ch){
            case 'T' : case 't' : animals[i] = new Tarantula(name, level); break;
            case 'H' : case 'h' : animals[i] = new Hamster(name, level); break;
            case 'C' : case 'c' : animals[i] = new Cat(name, level);   break;
        }
    }

    // daily
    string m; f >> m;
    day.resize(m.size());
    for( int j=0; j<m.size(); ++j ) {
        char d = m.at(j);
        switch(d){
            case 'b' : case 'B' : day[j] = Blue::instance();  break;
            case 'u' : case 'U' : day[j] = Usual::instance(); break;
            case 'j' : case 'J' : day[j] = Joyful::instance(); break;
        }
    }

}

void getMaxAnimal(vector<Animal*> &animals, vector<Day*> &day, vector<string>& names)
{
    names.clear();

  try{
    for( unsigned int i=0; i < day.size(); ++i){
        vector<pair<string, int>> nameHealth;
        int maxi = 0;
        string maxName;
        if(animals.size() == 0) return;

        int cnt = 0;
        for(int k = 0; k < animals.size(); k++){
            if(animals[k]->alive() && animals[k]->eLevel() >= 5) cnt++;
        }
        if(cnt == animals.size()) {

            if (day[i] == Usual::instance()) {
                day[i] = Joyful::instance();
            }
            else if(day[i] == Blue::instance()) day[i] = Usual::instance();
        }

        for(unsigned int j = 0; j < animals.size(); j++){
            if(animals[j]->alive()){
                animals[j]->takeCare(day[i]);
                if(animals[j]->alive())
                nameHealth.push_back({animals[j]->name(), animals[j]->eLevel()});
            }


        }
        for(auto it : nameHealth){
           if(it.second > maxi){
            maxi = it.second;
            maxName = it.first;
           }
        }

        if(nameHealth.size() == 0) {
            return;
        }
        names.push_back(maxName);
        ///cout <<"Day " << i + 1  << ": "<< maxName  << " " << maxi << endl; ///comment - for the test cases | uncomment - see eLevel as well
    }
  }catch(exception e){
    cout << e.what() << endl;
  }
}

void destroy(vector<Animal*> &animals)
{
    for(int i=0; i<(int)animals.size(); ++i) delete animals[i];
}

void destroyDay()
{
    Blue::destroy(); Usual::destroy(); Joyful::destroy();
}

///To change between the manual and the unit test mode
///#define NORMAL_MODE
#ifdef NORMAL_MODE

//Main function
int main()
{
    vector<Animal*> animals;
    vector<Day*> day;
    create("inp22.txt", animals, day);
    cout << "Given animals amount: " << animals.size() << endl;
    cout << "Given days amount: " << day.size() << endl;
    // Competition
    vector<string> names;
     cout << "-------------------------" << endl;
    getMaxAnimal(animals, day, names);
    for(int i = 0;  i < names.size(); i++) cout  << "Day " << i + 1 << ": " << names[i] << endl;
    if(names.size() == 0) cout << "All were given dead" << endl;
    else if(names.size() != day.size()) cout << "Next day:  no alive animal(s)" << endl;
    // Destruction of the objects
    destroy(animals);
    destroyDay();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "inp1*.txt")
{
    vector<Animal*> animals;
    vector<Day*> day;
    vector<string> names;

    create("inp11.txt", animals, day);
    getMaxAnimal(animals, day, names);
    CHECK(names.size() == 17);
    destroy(animals);

    create("inp12.txt", animals, day);
    getMaxAnimal(animals, day, names);
    CHECK(names.size() == 0);
    destroy(animals);

    create("inp13.txt", animals, day);
    getMaxAnimal(animals, day, names);
    CHECK(names.size() == 9);
    destroy(animals);

    destroyDay();
}


TEST_CASE("2", "inp2*.txt")
{
    vector<Animal*> animals;
    vector<Day*> day;
    vector<string> names;

    create("inp21.txt", animals, day);
    getMaxAnimal(animals, day, names);
    CHECK(names[1] == "Butterscotch");
    CHECK(names[names.size() - 1] == "Cat-man-do");
    destroy(animals);

    create("inp22.txt", animals, day);
    getMaxAnimal(animals, day, names);
    CHECK(names[names.size() - 1] == "Webster");
    CHECK(names[4] == "Butterscotch");
    destroy(animals);


    destroyDay();
}


TEST_CASE("3", "") {

    vector<Animal*> animals;
    vector<Day*> day;
    vector<string> names;

    animals.clear();
    day.clear();
    animals.push_back(new Tarantula("Spiderman", 20));
    getMaxAnimal(animals, day, names);

    CHECK(animals[0]->alive() == true);
    destroy(animals);


    animals.clear();
    day.clear();
    animals.push_back(new Tarantula("Webmaker", 4));
    day.push_back(Blue::instance());
    day.push_back(Joyful::instance());
    day.push_back(Usual::instance());
    getMaxAnimal(animals, day, names);

    CHECK(animals[0]->alive() == false);
    CHECK(day[0] == Blue::instance());
    CHECK(day[1] == Joyful::instance());
    CHECK(day[2] == Usual::instance());

    destroy(animals);


    animals.clear();
    day.clear();
    animals.push_back(new Hamster("Donnie", 30));
    day.push_back(Blue::instance());
    day.push_back(Joyful::instance());
    day.push_back(Usual::instance());
    names.clear();
    getMaxAnimal(animals, day, names);

    CHECK(animals[0]->alive() == true);
    CHECK(day[0] == Usual::instance());
    CHECK(day[1] == Joyful::instance());
    CHECK(day[2] == Joyful::instance());

    destroy(animals);

    animals.clear();
    day.clear();
    animals.push_back(new Cat("Cicacat", 7));
    day.push_back(Joyful::instance());
    day.push_back(Blue::instance());
    day.push_back(Blue::instance());

    getMaxAnimal(animals, day, names);

    CHECK(animals[0]->alive() == true);
    CHECK(day[0] == Joyful::instance());
    CHECK(day[1] == Usual::instance());
    CHECK(day[2] == Usual::instance());

    destroy(animals);

    destroyDay();
}

#endif // NORMAL_MODE

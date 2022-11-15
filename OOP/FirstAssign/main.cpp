#include <iostream>
#include "Matrix.h"
#define menuCount 6

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

class Menu
{
public:
    Menu(){}
    void run();
private:
    Matrix a;

    void menuDisplay();
    void read();
    void write();
    void getElem() const;
    void sum();
    void mult();
    void setElem();
};

int main()
{
    Menu m;
    m.run();

}

bool check(int a){return a>=0 && a<=menuCount;}

void Menu::run(){
    int n = 0;
    do{
        menuDisplay();
        cout << ">>>: ";
        cin >> n;
        if(check(n) == false) cout << "Please choose between 0-6" << endl;
        switch(n)
        {
            case 1:
                read();
                break;
            case 2:
                getElem();
                break;
            case 6:
                setElem();
                break;
            case 3:
                sum();
                break;
            case 4:
                mult();
                break;
            case 5:
                write();
                break;
        }
    } while(n != 0);
}

void Menu::menuDisplay()
{
    cout<<"****************************************\n";
    cout << " 0. - Quit" << endl;
    cout << " 1. - Read matrix" << endl;
    cout << " 2. - Get an element of the matrix" << endl;
    cout << " 3. - Add matrices" << endl;
    cout << " 4. - Multiply matrices" << endl;
    cout << " 5. - Write matrix" << endl;
    cout << " 6. - Set element of matrix" << endl;
    cout<<"****************************************\n";
}

void Menu::setElem(){
    cout << "Give index of i: ";
    int x;
    cin >> x;
    cout << "Give index of j: ";
    int y;
    cin >> y;
    cout << "Give setting number: ";
    int z;
    cin >> z;
    try
    {
        cout << "MATRIX[" << x << "][" << y  << "]: " << a.setElement(x, y, z) << endl;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::OVERINDEXED) cout << "Overindexing!" << endl;
        else if(ex == Matrix::NONINITIAL) cout << "Matrix is NOT initialized yet" << endl;
        else cout << "Unhandled exception!" << endl;
    }
}

void Menu::read(){
    try
    {
        cout << "This is your main matrix" << endl;
        cin >> a;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::INVALID)
        cout << "Invalid size!\nTry again with the number 2+" << endl;

        else cout << "Unhandled exeption!" << endl;
    }
}
void Menu::getElem() const {
    cout << "Give index of i: ";
    int x;
    cin >> x;
    cout << "Give index of j: ";
    int y;
    cin >> y;
    try
    {
        cout << "MATRIX[" << x << "][" << y  << "]: " << a.getElement(x, y) << endl;
    }

    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::OVERINDEXED) cout << "Overindexing!" << endl;
        else if(ex == Matrix::NONINITIAL) cout << "Matrix is NOT initialized yet" << endl;
        else cout << "Unhandled exception!" << endl;
    }
}
void Menu::sum(){
    try
    {
        cout << "Give me the second matrix to add to(with same size)" << endl;
        Matrix b;
        cin >> b;
        cout  << "This is your result matrix(sum)\n\n" << Matrix::add(a,b);
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::NONINITIAL) cout << "EMPTY!\nFirst main matrix is NOT initialized\nPlease input your main matrix first!" << endl;
        if(ex == Matrix::INVALID) cout << "Invalid size!" << endl;
        if(ex == Matrix::DIFFERENT) cout << "Different sizes!" << endl;
    }
}
void Menu::mult(){
    try
    {
        cout << "Give me the second matrix to multiply to(with same size)" << endl;
        Matrix b;
        cin >> b;
        cout << "This is your result matrix(product)" << endl << Matrix::mult(a,b);
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::NONINITIAL) cout << "EMPTY!\nFirst main matrix is NOT initialized\nPlease input your main matrix first!" << endl;
        if(ex == Matrix::INVALID) cout << "Invalid size!" << endl;
        if(ex == Matrix::DIFFERENT) cout << "Different sizes!" << endl;
    }
}
void Menu::write(){
    try
    {
        cout << "MATRIX:\n"<< a;
    }
    catch(Matrix::Exceptions ex)
    {
        if(ex == Matrix::NONINITIAL)  cout << "EMPTY!\nFirst main matrix is NOT initialized\nPlease input your main matrix first!" << endl;
    }
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Matrix.h"


TEST_CASE("creating, getting, setting", "Matrix") {
    Matrix m(3);
    m.setElement(1,1,5);
    CHECK(m.getElement(1,2) == 0);
    CHECK(m.getElement(1,1) == 5);
    CHECK(m.getSize() == 3);

    CHECK_THROWS(m.getElement(3,4) == Matrix::OVERINDEXED);

    Matrix n(5);
    CHECK(n.getSize() == 5);
    CHECK(n.getElement(2,2) == 0);
}

TEST_CASE("size checking"){
    Matrix a(3);
    Matrix b(4);
    CHECK(a.getSize() != b.getSize());
}

TEST_CASE("addition"){
    Matrix a(2);
    Matrix b(2);
    a.setElement(1,1,1);
    a.setElement(2,2,4);
    b.setElement(1,1,3);
    b.setElement(2,2,6);
    Matrix c = Matrix::add(a,b);
    CHECK(c.getElement(1,1) == 4);
    CHECK(c.getElement(2,2) == 10);
}

TEST_CASE("product"){
    Matrix a(3);
    Matrix b(3);
    a.setElement(1,1,1);
    a.setElement(2,2,3);
    a.setElement(3,3,5);
    a.setElement(1,3,2);
    a.setElement(3,1,4);
    b.setElement(1,1,1);
    b.setElement(2,2,2);
    b.setElement(3,3,3);
    b.setElement(1,3,4);
    b.setElement(3,1,5);
    Matrix c = Matrix::mult(a,b);
    CHECK(c.getElement(1,1) == 11);
    CHECK(c.getElement(2,2) == 6);
    CHECK(c.getElement(3,3) == 31);
    CHECK(c.getElement(1,3) == 10);
    CHECK(c.getElement(3,1) == 29);
}

TEST_CASE("exceptions"){
    Matrix a(3);
    CHECK_THROWS(a.getElement(3,4));
    CHECK_THROWS(a.getElement(-1,0));

    Matrix b(5);
    CHECK_THROWS(Matrix::add(a,b));
    CHECK_THROWS(Matrix::mult(a,b));

}
#endif // NORMAL_MODE














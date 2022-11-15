#include <iostream>
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"

using namespace std;

struct Fish
{
    string name;
    int amount;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is >> f.name >> f.amount;
        return is;
    }
};
/*----------------------1st task--------------------------*/
struct oneResult
{
    int oneSum;
    int oneCnt;
    int sizeSum;
    bool exist;

    oneResult() {}
    oneResult(bool e, int a, int s, int c) : exist(e), sizeSum(a), oneSum(s), oneCnt(c) {}
};

class lineSum : public Summation<Fish, oneResult>
{
    oneResult func(const Fish &f) const override { return oneResult(
                                    f.name == "catfish" && f.amount > 0,
                                    f.name == "catfish" ? f.amount : 0,
                                    f.name == "catfish" && f.amount > 0 ? 1 : 0, 1);
                        }
    oneResult neutral() const override { return oneResult(false,0, 0, 0); }
    oneResult add(const oneResult &a, const oneResult &b) const override
    {
        return oneResult(a.exist || b.exist, a.sizeSum + b.sizeSum, a.oneSum + b.oneSum, a.exist || b.exist ? 1 : 0);
    }
    bool cond(const Fish &f) const override
    {
        return f.name == "catfish";
    }
};

struct Contestant
{
    string name;
    string id;
    int sizeSum;
    int amount;
    bool exist;
    friend istream &operator>>(istream &is, Contestant &c)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss >> c.name >> c.id;
        StringStreamEnumerator<Fish> ss_enor(ss);
        lineSum pr;
        pr.addEnumerator(&ss_enor);
        pr.run();
        c.sizeSum = pr.result().sizeSum;
        c.exist = pr.result().exist;
        c.amount = pr.result().oneSum;
        return is;
    }
};

struct Result
{
    int sum;
    int sizeSum;
    int count;

    Result() : sum(0), sizeSum(0), count(0) {}
    Result(int s, int q, int c) : sum(s), sizeSum(q), count(c) {}
};

class Sumup : public Summation<Contestant, Result>
{
    Result func(const Contestant &e) const override
    {
        return Result(e.amount, e.sizeSum, e.exist ? 1 : 0);
    }
    Result neutral() const override { return Result(); }
    Result add(const Result &a, const Result &b) const override
    {
        return Result(a.sum + b.sum, a.sizeSum + b.sizeSum, b.count + a.count);
    }
};

/*----------------------2nd task--------------------------*/

struct Angler
{
    string name;
    int quantity;
    Angler() {}
    Angler(const string &n, int d) : name(n), quantity(d) {}
};

class whileSum : public Summation<Contestant, Angler>
{
public:
    whileSum(const string &name) : _name(name) {}

private:
    string _name;
    Angler func(const Contestant &c) const override { return Angler(c.name, c.amount); }
    Angler neutral() const override { return Angler("", 0); }
    Angler add(const Angler &a, const Angler &b) const override { return Angler(b.name, a.quantity + b.quantity); }
    void first() override {}
    bool whileCond(const Contestant &current) const override { return current.name == _name; }
};
// start
class ContestantEnumerator : public Enumerator<Angler>
{
private:
    SeqInFileEnumerator<Contestant> *_f;
    Angler _angler;
    bool _end;

public:
    ContestantEnumerator(const string &fname) { _f = new SeqInFileEnumerator<Contestant>(fname); }
    ~ContestantEnumerator() { delete _f; }
    void first() override
    {
        _f->first();
        next();
    }
    void next() override;
    bool end() const override { return _end; }
    Angler current() const override { return _angler; }
};
void ContestantEnumerator::next()
{
    _end = _f->end();
    if (_end)
        return;
    _angler.name = _f->current().name;
    whileSum pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler = pr.result();
}

class bestAngler : public MaxSearch<Angler, int>
{
    int func(const Angler &e) const override { return e.quantity; }
};

int main()
{

    try {
    string filename = "inp.txt";
    SeqInFileEnumerator<Contestant> ss_enor(filename);
    Sumup pr;
    pr.addEnumerator(&ss_enor);
    pr.run();
    if (pr.result().count != 0)
        cout << "The average number of caught catfishes: "
        << pr.result().sum / (double)pr.result().count << endl;
    else
    {
        cout << "No catfishes caught!" << endl;
        return 0;
    }

    bestAngler pp;
    ContestantEnumerator enor(filename);
    pp.addEnumerator(&enor);
    pp.run();
    if (pp.optElem().quantity != 0)
        cout << pp.optElem().name << " has caught most catfishes: " << pp.optElem().quantity << endl;
    else
        cout << "Nobody caught a catfish" << endl;
    } catch (SeqInFileEnumerator<Contestant>::Exceptions ex)
    {
        cout << "File not found" << endl;
    }
    return 0;
}

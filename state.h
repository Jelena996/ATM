#ifndef _STATE_H_
#define _STATE_H_

#include <string>
using namespace std;

class State
{
public:
    State(bool isPrototype = true);
    State(const State& state);
    virtual void execute();
    virtual void onEnter();   
    virtual void onExit();  //je li morala ova fja da bude virtuelna kad je svaka klasam samo poziva u svojoj
    virtual State* clone() const = 0;
    virtual void setView() const = 0;
    bool getIsPrototype() const;
    void setNextState(State* nextState);
    string getResult() const;
    void setResult(const string& result);
    friend ostream& operator<<(ostream& out, const State& state);
    virtual void printState(ostream& out) const;
    virtual string getName() const;

protected:
    bool isPrototype;
    State* nextState;
    string result;
};

class InitialState : public State
{
public:
    InitialState(bool isPrototype = true);
    virtual void execute();
    virtual void onEnter();
    virtual void onExit();
    virtual State* clone() const override;
    virtual void setView() const override;
    virtual void printState(ostream& out) const override;
    virtual string getName() const override;
};

class CardInputState : public State
{
public:
    CardInputState(bool isPrototype = true);
    virtual void execute();
    virtual void onEnter();
    virtual void onExit();
    virtual State* clone() const override;
    virtual void setView() const override;
    virtual void printState(ostream& out) const override;
    virtual string getName() const override;
private:
    string toDisplay;
};

class ServiceChoiceState : public State
{
public:
    ServiceChoiceState(bool isPrototype = true);
    virtual void execute();
    virtual void onEnter();
    virtual void onExit();
    virtual State* clone() const override;
    virtual void setView() const override;
    virtual void printState(ostream& out) const override;
    virtual string getName() const override;
};

class PrintReportState : public State
{
public:
    PrintReportState(bool isPrototype = true);
    virtual void execute();
    virtual void onEnter();
    virtual void onExit();
    virtual State* clone() const override;
    virtual void setView() const override;
    virtual void printState(ostream& out) const override;
    virtual string getName() const override;
};

class MoneyWithdrawState : public State
{
public:
    MoneyWithdrawState(bool isPrototype = true);
    virtual void execute();
    virtual void onEnter();
    virtual void onExit();
    virtual State* clone() const override;
    virtual void setView() const override;
    virtual void printState(ostream& out) const override;
    virtual string getName() const override;
};

#endif
#ifndef _SESSION_H_
#define _SESSION_H_

#include "state.h"
#include <vector>
#include <iostream>
#include "mytime.h"
using namespace std;

class Session
{
public:
    Session();
    Session(const Session& session);
    Session(Session&& session);
    ~Session();
    Session& operator=(const Session& session);
    Session& operator=(Session&& session);

    void start();
    void stop();
    int getId() const;
    time_t getStartTime() const;
    time_t getEndTime() const;
    void appendState(State* state);
    vector<State*>& getStates();

    friend ostream& operator<<(ostream& out, const Session& session);
private:
    static int totalId;
    int id;
    time_t startTime;
    time_t endTime;

    void empty();
    void copy(const Session& session);
    void move(Session& session);
    vector<State*> states;
};

#endif
#include "session.h"

int Session::totalId = 0;

Session::Session()
{
    id = ++totalId;
}

Session::Session(const Session& session)
{
    copy(session);
}

Session::Session(Session&& session)
{
    move(session);
}

Session::~Session()
{
    empty();
}

Session& Session::operator=(const Session& session)
{
    if (this != &session)
    {
        empty();
        copy(session);
    }

    return *this;
}

Session& Session::operator=(Session&& session)
{
    if (this != &session)
    {
        empty();
        move(session);
    }

    return *this;
}

void Session::start()
{
    startTime = getTimeNow();
}

void Session::stop()
{
    endTime = getTimeNow();
}

int Session::getId() const
{
    return id;
}

void Session::appendState(State* state)
{
    states.push_back(state);
}

vector<State*>& Session::getStates()
{
    return states;
}

ostream& operator<<(ostream& out, const Session& session)
{
    out << "Session id: " << session.id << endl;
    out << "Session start time: " << 0 << endl;
    out << "Session end time: " << 1 << endl;
    out << "Session states:" << endl << endl;
    for (int i = 0; i < session.states.size(); i++)
        out << *session.states[i] << endl;
    return out;
}

void Session::empty()
{
    states.erase(states.begin(), states.end());
}

void Session::copy(const Session& session)
{
    startTime = session.startTime;
    endTime = session.endTime;
    id = session.id;

    for (auto& state : session.states)  
    {
        states.push_back(state->clone());
    }
}

void Session::move(Session& session)
{
    startTime = session.startTime;
    endTime = session.endTime;
    id = session.id;

    states = session.states;
    session.states.clear();
}

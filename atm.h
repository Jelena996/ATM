#ifndef _ATM_H_
#define _ATM_H_

#include "exceptions.h"
#include "session.h"
#include "state.h"
#include <string>
#include "paymentcard.h"
#include <vector>
using namespace std;

class ATM
{
public:
    void createInstance(int id, const string& bankName, const string& location);
    static void destroyInstance();
    static ATM* getInstance();
    bool getIsEnd() const;
    void setIsEnd(bool value);
    enum StateEnum { INITIAL, CARDINPUT, SERVICECHOICE, PRINTREPORT, MONEYWITHDRAW };
    State* createState(StateEnum stateChoice);
    State* getCurrentState() const;
    void changeState(State* currentState, State* newState);
    ~ATM();
    vector<PaymentCard>& getPaymentCards();   //&
    void addPaymentCard(PaymentCard& paymentCard);
    PaymentCard* getPaymentCard(int id);
    void startNewSession();
    Session* getSession() const;
    PaymentCard* getCurrentCard() const;
    void setCurrentCard(PaymentCard* paymentCard);
    friend ostream& operator<<(ostream& out, const ATM& atm);
private:
	void createInstance(int id, const string& bankName, const string& location);
    static ATM* instance;
    ATM(int id, const string& bankName, const string& location);
    string bankName;
    string location;
    int id;
    State* currentState;
    bool isEnd;
    InitialState* initialStatePrototype;
    CardInputState* cardInputStatePrototype;
    ServiceChoiceState* serviceChoiceStatePrototype;
    PrintReportState* printReportStatePrototype;
    MoneyWithdrawState* moneyWithdrawStatePrototype;
    vector<PaymentCard> paymentCards;
    Session* currentSession;
    vector<Session*> sessions;
    PaymentCard* paymentCard;
};

#endif
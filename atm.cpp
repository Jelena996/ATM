#include "atm.h"
#include <fstream>
using namespace std;

ATM* ATM::instance = nullptr;

void ATM::createInstance(int id, const string& bankName, const string& location)
{
    if (instance == nullptr)
    {
        instance = new ATM(id, bankName, location);
        instance->changeState(nullptr, instance->createState(ATM::INITIAL));
    }
}

void ATM::destroyInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

ATM* ATM::getInstance()
{
    return instance;
}

bool ATM::getIsEnd() const   // poenta ove fje i setIsEnd
 {
    return isEnd;
}

void ATM::setIsEnd(bool value)
{
    isEnd = value;
}

State* ATM::createState(ATM::StateEnum stateChoice)
{
    switch (stateChoice)
    {
        case StateEnum::INITIAL: return initialStatePrototype->clone();
        case StateEnum::CARDINPUT: return cardInputStatePrototype->clone();
        case StateEnum::SERVICECHOICE: return serviceChoiceStatePrototype->clone();
        case StateEnum::PRINTREPORT: return printReportStatePrototype->clone();
        case StateEnum::MONEYWITHDRAW: return moneyWithdrawStatePrototype->clone();
        default: return nullptr;
    }
}

State* ATM::getCurrentState() const
{
    return currentState;
}

void ATM::changeState(State* currentState, State* newState)
{
    if (newState == nullptr)
        return;

    if (currentState != nullptr && currentState->getIsPrototype() == true)
        throw IllegalStateException();

    if (newState != nullptr && newState->getIsPrototype() == true)
        throw IllegalStateException();

    if (currentState != nullptr)
    {
        currentState->onExit();
    }
    this->currentState = newState;
    newState->onEnter();
}

ATM::ATM(int id, const string& bankName, const string& location)
{
    if (bankName == "")
        throw WrongBankNameException(bankName);

    if (location == "")
        throw WrongLocationException(location);

    this->id = id;
    this->bankName = bankName;
    this->location = location;
    currentSession = nullptr;
    isEnd = false;
    paymentCard = nullptr;

    initialStatePrototype = new InitialState(true);
    cardInputStatePrototype = new CardInputState(true);
    serviceChoiceStatePrototype = new ServiceChoiceState(true);
    printReportStatePrototype = new PrintReportState(true);
    moneyWithdrawStatePrototype = new MoneyWithdrawState(true);
}

ATM::~ATM()
{
    if (currentState != nullptr)
        currentState->onExit();
    if (currentSession != nullptr)
    {
        delete currentSession;
    }
	//-----objasniti
	//ispis bankomata u fajl pri zavrsavanju programa sa namjerom stavljen u destrukttor
    // print atm
    stringstream fileName;
    fileName << "atm_";
    fileName << getTimeNow();
    fileName << ".out";

    ofstream out;
    out.open(fileName.str(), ios::out);
    if (out.is_open())
    {
        out << *this;
		out.close();
    }

    delete initialStatePrototype;
    delete cardInputStatePrototype;
    delete serviceChoiceStatePrototype;
    delete printReportStatePrototype;
    delete moneyWithdrawStatePrototype;

    sessions.erase(sessions.begin(), sessions.end());
}

vector<PaymentCard>& ATM::getPaymentCards()
{
    return paymentCards;
}

void ATM::addPaymentCard(PaymentCard& paymentCard)
{
    paymentCards.push_back(paymentCard);
}

PaymentCard* ATM::getPaymentCard(int id)
{
    PaymentCard* paymentCard = nullptr;
    for (int i = 0; i < paymentCards.size(); i++)
    {
        if (paymentCards[i].getId() == id)
        {
            paymentCard = &paymentCards[i];
            break;
        }
    }

    return paymentCard;
}

void ATM::startNewSession()
{
    if (currentSession != nullptr)
        sessions.push_back(currentSession);

    currentSession = new Session();
}

Session* ATM::getSession() const
{
    return currentSession;
}

PaymentCard* ATM::getCurrentCard() const
{
    return paymentCard;
}

void ATM::setCurrentCard(PaymentCard* paymentCard)
{
    this->paymentCard = paymentCard;
}

ostream& operator<<(ostream& out, const ATM& atm)
{
    out << "Bank name: " << atm.bankName << endl;
    out << "Location: " << atm.location << endl;
    out << "ATM id: " << atm.id << endl;
    out << endl;
    out << "Sessions:" << endl;
    for (int i = 0; i < atm.sessions.size(); i++)
        out << *atm.sessions[i] << endl;
    return out;
}

#include <Windows.h>
#include "state.h"
#include <iostream>
#include "atm.h"
#include <sstream>
#include <fstream>
using namespace std;

// State

State::State(bool isPrototype)
{
    this->isPrototype = isPrototype;
    nextState = nullptr;
}


State::State(const State& state)
{
    this->isPrototype = false;
}



//zasta ce mi ova funkicja 
void State::execute()
{
    if (nextState != nullptr)
        ATM::getInstance()->changeState(this, nextState);
}


void State::onEnter()
{
    setView();
}

void State::onExit()
{
    if (ATM::getInstance()->getSession() != nullptr)
        ATM::getInstance()->getSession()->appendState(this);
}
bool State::getIsPrototype() const
{
    return isPrototype;
}

void State::setNextState(State* nextState)
{
    this->nextState = nextState;
}

string State::getResult() const
{
    return result;
}

void State::setResult(const string& result)
{
    this->result = result;
}

ostream& operator<<(ostream& out, const State& state)
{
    state.printState(out);
    return out;
}

void State::printState(ostream& out) const
{
    out << "State info:" << endl;
    out << "Name = " << getName() << endl;
    out << "Result = " << getResult() << endl;
}

string State::getName() const
{
    return "State";
}


// Initial state
InitialState::InitialState(bool isPrototype)
    : State(isPrototype)
{

}

void InitialState::execute()
{
    int choice;
    cin >> choice;

    switch (choice)
    {
        case 0: result = "0"; ATM::getInstance()->setIsEnd(true); break;
        case 1: result = "1"; ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::CARDINPUT)); break;
         default: result = "Nonexistent option selected"; ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::INITIAL));
    }
}

void InitialState::onEnter()
{
    setView();
}

void InitialState::onExit()
{
    ATM::getInstance()->startNewSession();
    State::onExit();
}

State* InitialState::clone() const
{
    return new InitialState(*this);
}

void InitialState::setView() const
{
    //objasniti 
	system("cls");

    cout << "Enter choice:" << endl;
    cout << "0. exit" << endl;
    cout << "1. read a card" << endl;
}

void InitialState::printState(ostream& out) const
{
    State::printState(out);
}

string InitialState::getName() const
{
    return "InitialState";
}


// CardInputState
CardInputState::CardInputState(bool isPrototype)
    : State(isPrototype)
{

}

void CardInputState::execute()
{
    vector<PaymentCard>& paymentCards = ATM::getInstance()->getPaymentCards();

    int cardNumber;
    cin >> cardNumber;
    if (cardNumber == 0)
    {
        result = "0";
        ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::INITIAL));
    }
    else if (cardNumber > paymentCards.size() || cardNumber < 0)
    {
        result = "Incorrect card number choice";
        cout << "Incorrect card number choice" << endl;
        ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::CARDINPUT));
    }
    else
    {
        result = to_string(paymentCards[cardNumber - 1].getId());
        ATM::getInstance()->setCurrentCard(&paymentCards[cardNumber - 1]);
        ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::SERVICECHOICE));
    }
}

void CardInputState::onEnter()
{
    stringstream stream;
    vector<PaymentCard>& paymentCards = ATM::getInstance()->getPaymentCards();
    for (int i = 0; i < paymentCards.size(); i++)
        stream << (i + 1) << ". " << paymentCards[i].getId() << endl;

    toDisplay = stream.str();  //vraca kopiju trenutnog sadrzaja
    setView();

    ATM::getInstance()->setCurrentCard(nullptr);
}

void CardInputState::onExit()
{
    State::onExit();
}

State* CardInputState::clone() const
{
    return new CardInputState(*this);
}

void CardInputState::setView() const
{
   //ovo samo cisti ekran system("cls");

    cout << toDisplay << endl;
    cout << "Enter card number:" << endl;
}

void CardInputState::printState(ostream& out) const
{
    State::printState(out);
}

string CardInputState::getName() const
{
    return "CardInputState";
}


// ServiceChoiceState
ServiceChoiceState::ServiceChoiceState(bool isPrototype)
    : State(isPrototype)
{

}

void ServiceChoiceState::execute()
{
    int choice;
    cin >> choice;

    switch (choice)
    {
        case 1: result = "1"; ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::MONEYWITHDRAW)); break;
        case 2: result = "2"; ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::PRINTREPORT)); break;
        case 3: result = "3"; ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::INITIAL)); break;
        default: result = "Nonexistent option selected"; ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::SERVICECHOICE)); break;
    }
}

void ServiceChoiceState::onEnter()
{
    setView();
}

void ServiceChoiceState::onExit()
{
    State::onExit();
}

State* ServiceChoiceState::clone() const
{
    return new ServiceChoiceState(*this);
}

void ServiceChoiceState::setView() const
{
    PaymentCard* paymentCard = ATM::getInstance()->getCurrentCard();
    if (paymentCard == nullptr)
        throw InvalidPaymentCardSelectedException();

    system("cls");

    cout << "Client: " << paymentCard->getClient() << endl;
    cout << "Card number: " << paymentCard->getId() << endl;

    cout << "Choose service:" << endl;
    cout << "1. Withdraw money" << endl;
    cout << "2. Print report" << endl;
    cout << "3. Back to start" << endl;
}

void ServiceChoiceState::printState(ostream& out) const
{
    State::printState(out);
}

string ServiceChoiceState::getName() const
{
    return "ServiceChoiceState";
}


// PrintReportState
PrintReportState::PrintReportState(bool isPrototype)
    : State(isPrototype)
{

}

void PrintReportState::execute()
{
	Sleep(15000);
  //da se objasni i treba li ja nesto da mijenjam na odbrani, kad mi daju ime fajla -------------------
	stringstream fileName;
    fileName << "report_";
    fileName << getTimeNow();
    fileName << ".out";

    ofstream out;
    out.open(fileName.str(), ios::out);
    if (out.is_open())
    {
        PaymentCard* paymentCard = ATM::getInstance()->getCurrentCard();
        if (paymentCard)
        {
            out << "Client: " << paymentCard->getClient() << endl;
            out << "Card number: " << paymentCard->getId() << endl;
            time_t timeValue = getTimeNow();
            out << "Report date: " << getDateFormatted(timeValue) << endl;
            out << "Report time: " << getTimeFormatted(timeValue) << endl;
            out << "Balance: " << paymentCard->getBalance() << endl;
            out << endl;

            result = fileName.str();
        }
        else
            result = "Can't open file " + fileName.str();
        out.close();
    }

    ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::SERVICECHOICE));
}

void PrintReportState::onEnter()
{
    setView();
}

void PrintReportState::onExit()
{
    State::onExit();
}

State* PrintReportState::clone() const
{
    return new PrintReportState(*this);
}

void PrintReportState::setView() const
{
    system("cls");

    cout << "Report print in progress..." << endl;
}

void PrintReportState::printState(ostream& out) const
{
    State::printState(out);
}

string PrintReportState::getName() const
{
    return "PrintReportState";
}


// MoneyWithdrawState
MoneyWithdrawState::MoneyWithdrawState(bool isPrototype)
    : State(isPrototype)
{

}

void MoneyWithdrawState::execute()
{
    cout << "Enter amount to withdraw:" << endl;

    unsigned int withdrawAmount;
    cin >> withdrawAmount;
    
    PaymentCard* card = ATM::getInstance()->getCurrentCard();
    if (card == nullptr)
        throw InvalidPaymentCardSelectedException();

    if (withdrawAmount > card->getBalance())
    {
        result = "Invalid withdraw amount";
        ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::MONEYWITHDRAW));
    }
    else
    {
        card->withdraw(withdrawAmount);
        // ime, card id, datum i vreme isplate, iznos, preostalo
        //result = putanja fajla
        
        stringstream fileName;
        fileName << "receipt_";
        fileName << getTimeNow();
        fileName << ".out";

        ofstream out;
        out.open(fileName.str(), ios::out);
        if (out.is_open())
        {
            PaymentCard* paymentCard = ATM::getInstance()->getCurrentCard();
			if (paymentCard)
			{
				out << "Client: " << paymentCard->getClient() << endl;
				out << "Card number: " << paymentCard->getId() << endl;
				time_t timeValue = getTimeNow();
				//--------------getDateFormatted
				out << "Payment date: " << getDateFormatted(timeValue) << endl;
				out << "Payment time: " << getTimeFormatted(timeValue) << endl;
				out << "Withdraw amount: " << withdrawAmount << endl;
				out << "New balance: " << paymentCard->getBalance() << endl;
				out << endl;

				result = fileName.str();
			}
            else
                result = "Can't open file " + fileName.str();
            out.close();
        }
        ATM::getInstance()->changeState(this, ATM::getInstance()->createState(ATM::SERVICECHOICE));
    }
}

void MoneyWithdrawState::onEnter()
{
    setView();
}

void MoneyWithdrawState::onExit()
{
    State::onExit();
}

State* MoneyWithdrawState::clone() const
{
    return new MoneyWithdrawState(*this);
}

void MoneyWithdrawState::setView() const
{
    system("cls");
}

void MoneyWithdrawState::printState(ostream& out) const
{
    State::printState(out);
}

string MoneyWithdrawState::getName() const
{
    return "MoneyWithdrawState";
}

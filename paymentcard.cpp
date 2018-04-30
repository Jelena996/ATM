#include "paymentcard.h"

// pocetni id, da se malo vise razlikuje od rednog broja u cardinputstate
int PaymentCard::totalId = 1230;

PaymentCard::PaymentCard(string client)
{
    if (client == "")
    {
        throw WrongClientNameException(client);
    }
    id = ++totalId;
    this->client = client;
    balance = 0;
}

void PaymentCard::deposit(unsigned int amount)
{
    balance += amount;
}

void PaymentCard::withdraw(unsigned int amount)
{
    if (balance < amount)
    {
        throw WrongAmountException(balance, amount);
    }

    balance -= amount;
}

int PaymentCard::getId() const
{
    return id;
}

string PaymentCard::getClient() const
{
    return client;
}

unsigned int PaymentCard::getBalance() const
{
    return balance;
}

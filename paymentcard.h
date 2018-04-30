#ifndef _PAYMENTCARD_H_
#define _PAYMENTCARD_H_

#include <string>
#include "exceptions.h"
using namespace std;

class PaymentCard
{
public:
    PaymentCard(string client);
    void deposit(unsigned int amount);
    void withdraw(unsigned int amount);
    int getId() const;
    string getClient() const;
    unsigned int getBalance() const;
private:
    static int totalId;
    int id;
    string client;
    unsigned int balance;
};

#endif
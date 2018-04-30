#include "paymentcard.h"
#include "atm.h"
#include "state.h"
#include <iostream>
#include "paymentcard.h"
using namespace std;

int main()
{
    try
    {
        ATM::getInstance()->createInstance(522, "milee", "Belgrade");
		ATM::getInstance()->createInstance(54, "milll", "crna");

        PaymentCard p1("Petar"), p2("Mitar"), p3("Zivko"), p4("Baraka Obama");
        p1.deposit(200); p2.deposit(300); p3.deposit(150); p4.deposit(1);

        // addPaymentCard kopira karticu u niz kartica, a onda se koristi uvek
        // ona kartica iz niza kartica u ATM-u, ne moze preko p1, p2, p3, p4
        ATM::getInstance()->addPaymentCard(p1);
        ATM::getInstance()->addPaymentCard(p2);
        ATM::getInstance()->addPaymentCard(p3);
        ATM::getInstance()->addPaymentCard(p4);

        while (ATM::getInstance()->getIsEnd() == false)
            ATM::getInstance()->getCurrentState()->execute();

        ATM::destroyInstance();


	
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        // ako pukne u try pre nego sto uradi ovo
        ATM::destroyInstance();
    }

    return 0;
}

#ifndef _MYTIME_H_
#define _MYTIME_H_

#include <ctime>
#include <string>
using namespace std;

time_t getTimeNow();
string getTimeFormatted(time_t timeValue);
string getDateFormatted(time_t timeValue);

#endif
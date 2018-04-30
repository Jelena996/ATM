#include "mytime.h"

time_t getTimeNow()
{
    return time(NULL);
}

string getTimeFormatted(time_t timeValue)
{
    struct tm* currentLocalTime = localtime(&timeValue);
    char dateTimeString[100 + 1];
    if (currentLocalTime != nullptr)
    {
        strftime(dateTimeString, 100, "%H:%M:%S", currentLocalTime);
        string result = string(dateTimeString);
        return result;
    }
    else
    {
        return "<unkonwn time>";
    }
}

string getDateFormatted(time_t timeValue)
{
    struct tm* currentLocalTime = localtime(&timeValue);
    char dateTimeString[100 + 1];
    if (currentLocalTime != nullptr)
    {
        strftime(dateTimeString, 100, "%Y.%d.%m.", currentLocalTime);
        string result = string(dateTimeString);
        return result;
    }
    else
    {
        return "<unkonwn date>";
    }
}

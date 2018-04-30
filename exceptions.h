#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//za exceptions treba da se koriste strukture iz standardne biblioteke(objasniti exceptions)
//objasniti ispis u fajlove i mytime.cpp
//staticka biblioteka //trebaju li neki makroi i problemi prilikom povezivanja na uvidu (test fja)
//objansiti try u main-u


class WrongAmountException : public exception
{
public:
    WrongAmountException(unsigned int balance, unsigned int withdrawAmount)
    {
        stringstream messageStream;
        messageStream << "Wrong amount of money: balance = " << balance << ", withdraw amount = " << withdrawAmount;
        message = messageStream.str();
    }
    virtual char const* what() const override
    {
        return message.c_str();
    }
private:
    string message;
};

class WrongClientNameException : public exception
{
public:
    WrongClientNameException(const string& clientName)
    {
        message = "Wrong client name: ";
        if (clientName == "")
            message += "<empty>";
        else
            message += clientName;
    }
    virtual char const* what() const override
    {
        return message.c_str();
    }
private:
    string message;
};

class WrongBankNameException : public exception
{
public:
    WrongBankNameException(const string& bankName)
    {
        message = "Wrong bank name: ";
        if (bankName == "")
            message += "<empty>";
        else
            message += bankName;
    }
    virtual char const* what() const override
    {
        return message.c_str();
    }
private:
    string message;
};

class WrongLocationException : public exception
{
public:
    WrongLocationException(const string& location)
    {
        message = "Wrong location name: ";
        if (location == "")
            message += "<empty>";
        else
            message += location;
    }
    virtual char const* what() const override
    {
        return message.c_str();
    }
private:
    string message;
};

class IllegalStateException : public exception
{
public:
    IllegalStateException()
    {
        message = "Prototype state used";
    }
    virtual char const* what() const override
    {
        return message.c_str();
    }
private:
    string message;
};

class InvalidPaymentCardSelectedException : public exception
{
public:
    InvalidPaymentCardSelectedException()
    {
        message = "Invalid payment card selected";
    }
    virtual char const* what() const override
    {
        return message.c_str();
    }
private:
    string message;
};

#endif
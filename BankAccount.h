#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount 
{
  public:
    static const int MAX_SIZE = 30;

    BankAccount(int = 0, std::string = "", std::string = "", double = 0.0);
    ~BankAccount();

    void setAccountNumber(int);
    void setLastName(std::string);
    void setFirstName(std::string);
    void setBalance(double);

    int getAccountNumber() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    double getBalance() const;

  private:
    int accountNumber;
    char firstName[MAX_SIZE];
    char lastName[MAX_SIZE];
    double balance;
};

#endif

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount 
{
  public:
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
    std::string firstName;
    std::string lastName;
    double balance;
};

#endif

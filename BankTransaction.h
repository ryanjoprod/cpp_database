#ifndef BANKTRANSACTION_H
#define BANKTRANSACTION_H

#include "BankAccount.h"
#include <mariadb/conncpp.hpp>
#include <string>

class BankAccount;

class BankTransaction 
{
  public:
    BankTransaction(const std::string = "localhost", const std::string = "", const std::string = "", const std::string = "");
    ~BankTransaction();

    void createAccount(BankAccount*);
    void closeAccount(int);
    void deposit(int, double);
    void withdraw(int, double);
    BankAccount* getAccount(int);
    void printAllAccount();
    void message(std::string);

  private:
    std::unique_ptr<sql::Connection> conn = nullptr;
};

#endif

#ifndef BANKTRANSACTION_H
#define BANKTRANSACTION_H

#include "BankAccount.h"
#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>

class BankAccount;

class BankTransaction 
{
  public:
    BankTransaction();
    ~BankTransaction();

    void createAccount(const std::unique_ptr<sql::Connection>&, BankAccount*);
    void closeAccount(const std::unique_ptr<sql::Connection>&, int);
    void deposit(const std::unique_ptr<sql::Connection>&, int, double);
    void withdraw(const std::unique_ptr<sql::Connection>&, int, double);
    BankAccount* getAccount(const std::unique_ptr<sql::Connection>&, int);
    void printAllAccounts(const std::unique_ptr<sql::Connection>&);
    void message(std::string);
};

#endif

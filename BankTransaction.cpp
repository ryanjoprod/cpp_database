#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>

#include "BankTransaction.h"
#include "BankAccount.h"

BankTransaction::BankTransaction() {}

BankTransaction::~BankTransaction() {}

BankAccount* BankTransaction::getAccount(const std::unique_ptr<sql::Connection> &connection, int accountNumber)
{
  BankAccount* bankAccount = new BankAccount;

  try {
    std::unique_ptr<sql::PreparedStatement> stmnt(connection->prepareStatement("select * from BankAccount where accountNumber = ?"));

    stmnt->setInt(1, accountNumber);

    sql::ResultSet *res = stmnt->executeQuery();

    while (res->next()) {
      std::cout << "Account Number: " << res->getInt(1) << std::endl;
      bankAccount->setAccountNumber(res->getInt(1));
      std::cout << "bankAccountNumber: " << bankAccount->getAccountNumber() << std::endl;
      std::cout << "First Name: " << res->getString(2).c_str() << std::endl;
      bankAccount->setFirstName(static_cast<std::string>(res->getString(2).c_str()));
      std::cout << "Last Name: " << res->getString(3).c_str() << std::endl;
      bankAccount->setLastName(static_cast<std::string>(res->getString(3).c_str()));
      std::cout << "Balance: " << res->getDouble(4) << std::endl;
      bankAccount->setBalance(res->getDouble(4));
    }
  }
  catch(sql::SQLException& e) {
    std::cerr << "Failed to get bank account! " << e.what() << std::endl;
  }

  return bankAccount;
}

void BankTransaction::withdraw(const std::unique_ptr<sql::Connection> &connection, int accountNumber, double amount)
{
  BankAccount* bankAccount = getAccount(connection, accountNumber);
  
  if (bankAccount != NULL) {
    if (bankAccount->getBalance() < amount) {
      message("Cannot withdraw. Try lower amount.");
    }
    else {
      try {
        bankAccount->setBalance(bankAccount->getBalance() - amount);
        std::unique_ptr<sql::PreparedStatement> stmnt(connection->prepareStatement("update BankAccount set balance = ? where accountNumber = ?"));
        
        stmnt->setDouble(1, bankAccount->getBalance());
        stmnt->setInt(2, accountNumber);

        stmnt->executeQuery();

        message("Cash withdrawl successful. Balance updated.");
      }
      catch (sql::SQLException& e) {
        std::cerr << "Cash withdrawl unsuccessful. " << e.what() << std::endl;
      }
    }
  }
}

void BankTransaction::deposit(const std::unique_ptr<sql::Connection> &connection, int accountNumber, double amount)
{

  try {
    std::unique_ptr<sql::PreparedStatement> stmnt(connection->prepareStatement("update BankAccount set balance = balance + ? where accountNumber = ?"));

    stmnt->setDouble(1, amount);
    stmnt->setInt(2, accountNumber);

    stmnt->executeQuery();

    message("Deposit successful. Balance updated!");
  }
  catch (sql::SQLException& e) {
    std::cerr << "Deposit unsuccessful. Update failed!" << e.what() << std::endl;
  }
}

void BankTransaction::createAccount(const std::unique_ptr<sql::Connection> &connection, BankAccount* bankAccount)
{
  try {
    std::unique_ptr<sql::PreparedStatement> stmnt(connection->prepareStatement("insert into BankAccount (accountNumber, firstName, lastName, balance) values (?, ?, ?, ?)"));
    
    stmnt->setInt(1, bankAccount->getAccountNumber());
    stmnt->setString(2, static_cast<sql::SQLString>(bankAccount->getFirstName()));
    stmnt->setString(3, static_cast<sql::SQLString>(bankAccount->getLastName()));
    stmnt->setDouble(4, bankAccount->getBalance());

    stmnt->executeQuery();

    message("Account creation successful!");
  }
  catch (sql::SQLException &e) {
    std::cerr << "Account creation unsuccessful: " << e.what() << std::endl;
  }
}

void BankTransaction::closeAccount(const std::unique_ptr<sql::Connection> &connection, int accountNumber)
{
  try {
    std::unique_ptr<sql::PreparedStatement> stmnt(connection->prepareStatement("delete from BankAccount where accountNumber = ?"));

    stmnt->setInt(1, accountNumber);

    stmnt->executeQuery();

    message("Account deletion successful");
  }
  catch(sql::SQLException& e) {
    std::cerr << "Account deletion unsuccessful: " << e.what() << std::endl;
  }
}

void BankTransaction::message(std::string message)
{
  std::cout << message << std::endl;
}

void BankTransaction::printAllAccounts(const std::unique_ptr<sql::Connection> &connection)
{
  try {
    std::unique_ptr<sql::PreparedStatement> stmnt(connection->prepareStatement("select * from BankAccount"));

    sql::ResultSet *res = stmnt->executeQuery();

    std::cout << std::left << std::setw(10) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << '+' << '+' << std::endl;
    std::cout << std::setfill(' ') << '|' << std::left << std::setw(9) << "Account" << std::setfill(' ') << '|' << std::setw(20) << "First Name" << std::setfill(' ') << '|' << std::setw(20) << "Last Name" << std::setfill(' ') << '|' << std::right << std::setw(20) << "Balance" << '|' << std::endl;
    std::cout << std::left << std::setw(10) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << '+' << '+' << std::endl;

    while(res->next()) {
      std::cout << std::setfill(' ') << '|' << std::left << std::setw(9) << res->getInt(1) << std::setfill(' ') << '|' << std::setw(20) << res->getString(2).c_str() << std::setfill(' ') << '|' << std::setw(20) << res->getString(3).c_str() << std::setfill(' ') << '|' << std::right << std::setw(20) << res->getDouble(4) << '|' << std::endl;
    }

    std::cout << std::left << std::setw(10) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << '+' << '+' << std::endl;
  }
  catch (sql::SQLException& e) {
    std::cerr << "Error printing all accounts! " << e.what() << std::endl;
  }
}

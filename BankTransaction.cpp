#include <cstdlib>
#include <cstring>
#include <mariadb/conncpp.hpp>
#include <memory>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "BankTransaction.h"
#include "BankAccount.h"

BankTransaction::BankTransaction(const std::string HOST, const std::string USER, const std::string PASSWORD, const std::string DATABASE)
{
  // Instantiate driver
  sql::Driver* driver = sql::mariadb::get_driver_instance();
  
  // Configure connection
  sql::SQLString url("jdbc:mariadb://" + HOST + ":3306/" + DATABASE);
  sql::Properties properties({{"user", USER}, {"password", PASSWORD}});

  // Establish connection
  std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

  if (!conn) {
    std::cerr << "Invalid database connection" << std::endl;
    exit(EXIT_FAILURE);
  }
}

BankTransaction::~BankTransaction()
{
  conn->close();
}

BankAccount* BankTransaction::getAccount(int acno)
{
  BankAccount* b = NULL;
  MYSQL_RES* rset;
  MYSQL_ROW row;
  std::stringstream sql;
  sql << "SELECT * FROM bank_account WHERE acc_no=" << acno;

  if (!mysql_query(conn, sql.str().c_str()))
  {
    b = new BankAccount();
    rset = mysql_use_result(conn);
    row = mysql_fetch_row(rset);
    b->setAccountNumber(atoi(row[0]));
    b->setFirstName(row[1]);
    b->setLastName(row[2]);
    b->setBalance(atof(row[3]));
  }

  mysql_free_result(rset);
  return b;
}

void BankTransaction::withdraw(int acno, double amount)
{
  BankAccount* b = getAccount(acno);
  if (b != NULL)
  {
    if (b->getBalance() < amount)
      message("Cannot withdraw. Try lower amount.");
    else
    {
      b->setBalance(b->getBalance() - amount);
      std::stringstream sql;
      sql << "UPDATE bank_account SET balance=" << b->getBalance() << " WHERE acc_no=" << acno;

      if (!mysql_query(conn, sql.str().c_str()))
        message("Cash withdrawl successful. Balance updated.");
      else
        message("Cash withdrawl unsuccessful. Update failed!");
    }
  }
}

void BankTransaction::deposit(int acno, double amount)
{
  std::stringstream sql;
  sql << "UPDATE bank_account SET balance=balance+" << amount << " WHERE acc_no=" << acno;

  if (!mysql_query(conn, sql.str().c_str()))
    message("Cash deposit successful. Balance updated!");
  else
    message("Cash deposit unsuccessful! Update failed!");
}

void BankTransaction::createAccount(BankAccount* ba)
{
  std::stringstream ss;
  ss << "INSERT INTO bank_account(acc_no, fname, lname, balance)" << "values (" << ba->getAccountNumber() << ", '" << ba->getFirstName() + "','" << ba->getLastName() << "'," << ba->getBalance() << ")";

  if (mysql_query(conn, ss.str().c_str()))
    message("Failed to create account!");
  else
    message("Account creation successful.");
}

void BankTransaction::closeAccount(int acno)
{
  std::stringstream ss;
  ss << "DELETE FROM bank_account WHERE acc_no=" << acno;

  if (mysql_query(conn, ss.str().c_str()))
    message("Failed to close account.");
  else
    message("Account close successful.");
}

void BankTransaction::message(std::string msg)
{
  std::cout << msg << std::endl;
}

void BankTransaction::printAllAccount()
{
  MYSQL_RES* rset;
  MYSQL_ROW rows;
  std::string sql = "SELECT * FROM bank_account";

  if (mysql_query(conn, sql.c_str())) 
  {
    message("Error printing all account!");
    return;
  }

  rset = mysql_use_result(conn);

  std::cout << std::left << std::setw(10) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << '+' << '+' << std::endl;
  std::cout << std::setfill(' ') << '|' << std::left << std::setw(9) << "Account" << std::setfill(' ') << '|' << std::setw(20) << "First Name" << std::setfill(' ') << '|' << std::setw(20) << "Last Name" << std::setfill(' ') << '|' << std::right << std::setw(20) << "Balance" << '|' << std::endl;
  std::cout << std::left << std::setw(10) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << '+' << '+' << std::endl;

  if (rset)
  {
    while((rows = mysql_fetch_row(rset)))
    {
      std::cout << std::setfill(' ') << '|' << std::left << std::setw(9) << rows[0] << std::setfill(' ') << '|' << std::setw(20) << rows[1] << std::setfill(' ') << '|' << std::setw(20) << rows[2] << std::setfill(' ') << '|' << std::right << std::setw(20) << rows[3] << '|' << std::endl;
    }

    std::cout << std::left << std::setw(10) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << std::left << '+' << std::setw(21) << std::setfill('-') << '+' << '+' << std::endl;
  }

  mysql_free_result(rset);
}

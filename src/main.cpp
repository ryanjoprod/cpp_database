#include <iostream>
#include <mariadb/conncpp/Statement.hpp>
#include <fstream>
#include <cstdlib>
#include <mariadb/conncpp.hpp>
#include <ostream>
#include <string>

#include "BankAccount.h"
#include "BankTransaction.h"

enum Options
{
  PRINT = 1,
  NEW,
  WITHDRAW,
  DEPOSIT,
  CLOSE,
  END
};

int mainMenu()
{
  std::cout << "\nMenu Options" <<std::endl
    << "1 - Print All Accounts" << std::endl
    << "2 - Open New Account" << std::endl
    << "3 - Withdraw" << std::endl
    << "4 - Deposit" << std::endl
    << "5 - Close Account" <<std::endl
    << "6 - End Transaction" << std::endl
    << "? " << std::endl;

  int ch;
  std::cin >> ch;
  return ch;
}

int main(int argc, char** argv)
{
  try {
    // Instantiate driver
    sql::Driver* driver = sql::mariadb::get_driver_instance();

    // Configure connection
    sql::SQLString url("jdbc:mariadb://localhost:3306/fakeBank");
    sql::Properties properties({{"user", argv[1]}, {"password", argv[2]}});

    // Establish connection
    std::unique_ptr<sql::Connection> connection(driver->connect(url, properties));

    // BankTransaction* bankTransaction = new BankTransaction(host, user, password, database);
    BankTransaction* bankTransaction = new BankTransaction();

    int choice;
    int accountNumber;
    std::string firstName, lastName;
    double balance;

    while (1)
    {
      choice = mainMenu();

      if (choice == END) break;

      switch (choice)
      {
        case PRINT:
          bankTransaction->printAllAccounts(std::move(connection));
          break;
        case NEW:
          std::cout << "\nEnter account no, first name, last name, balance: " << std::endl << "? ";
          std::cin >> accountNumber;
          std::cin >> firstName;
          std::cin >> lastName;
          std::cin >> balance;

          if (accountNumber < 1)
          {
            std::cout << "Invalid account number." << std::endl;
            break;
          }

          bankTransaction->createAccount(std::move(connection), new BankAccount(accountNumber, firstName, lastName, balance));
          break;
        case WITHDRAW:
          std::cout << "\nEnter account no, amount to Withdraw" << std::endl << "? ";
          std::cin >> accountNumber;
          std::cin >> balance;

          if (balance < 0)
          {
            std::cout << "Invalid Amount." << std::endl;
            break;
          }

          bankTransaction->withdraw(std::move(connection), accountNumber, balance);
          break;
        case DEPOSIT:
          std::cout << "\nEnter account no, amount to deposit " << std::endl << "? ";
          std::cin >> accountNumber;
          std::cin >> balance;

          if (balance < 0)
          {
            std::cout << "Invalid amount." << std::endl;
            break;
          }

          bankTransaction->deposit(std::move(connection), accountNumber, balance);
          break;
        case CLOSE:
          std::cout << "\nEnter account number to close account " << std::endl << "? ";
          std::cin >> accountNumber;
          bankTransaction->closeAccount(std::move(connection), accountNumber);
          break;
        default:
          std::cerr << "Invalid choice!" << std::endl;
          break;
      }
    }
  }
  catch(sql::SQLException& e) {
    std::cerr << "Database connection failure: " << e.what() << std::endl;

    std::cout << "Would you like to create the database (Y/n)";
    std::string input;
    std::cin >> input;

    if (input.compare("y") == 0 || input.compare("Y") == 0)
    {
      // Instantiate driver
      sql::Driver* driver = sql::mariadb::get_driver_instance();

      // Configure connection
      sql::SQLString url("jdbc:mariadb://localhost:3306");
      sql::Properties properties({{"user", argv[1]}, {"password", argv[2]}});

      // Establish connection
      std::unique_ptr<sql::Connection> connection(driver->connect(url, properties));

      std::unique_ptr<sql::Statement> stmnt(connection->createStatement());
      std::ifstream inf{"fakeBank.sql"};
      if (!inf)
      {
        std::cerr << "Was not able to open fakeBank.sql\n";
        return 1;
      }

      std::string dbCreationString;

      while (inf)
      {
        std::string strInput;
        std::getline(inf, strInput);
        dbCreationString.append(strInput);
        if (dbCreationString.find(';') != std::string::npos)
        {
          stmnt->execute(static_cast<sql::SQLString>(dbCreationString));
          dbCreationString = "";
        }
      }
      inf.close();
      std::cout << "Database created!";
      mainMenu();
    }
    else if (input.compare("n") == 0 || input.compare("N") == 0) {
      std::cout << "Program will exit now." << std::endl;
      exit(EXIT_FAILURE);
    }
    else {
      std::cout << "Program will exit now." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}

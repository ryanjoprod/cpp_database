#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <mariadb/conncpp.hpp>
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
    << "6 - End Transaction" << std::endl;

  int ch;
  std::cin >> ch;
  return ch;
}

int main(int argc, char** argv)
{
  BankTransaction* bankTransaction = new BankTransaction(host, user, password, database);

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
        bankTransaction->printAllAccount();
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

        bankTransaction->createAccount(new BankAccount(accountNumber, firstName, lastName, balance));
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
        
        bankTransaction->withdraw(accountNumber, balance);
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
        
        bankTransaction->deposit(accountNumber, balance);
        break;
      case CLOSE:
        std::cout << "\nEnter account number to close account " << std::endl << "? ";
        std::cin >> accountNumber;
        bankTransaction->closeAccount(accountNumber);
        break;
      default:
        std::cerr << "Invalid choice!" << std::endl;
        break;
    }
  }

  return 0;
}

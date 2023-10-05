#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <mariadb/mysql.h>
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
  BankTransaction* bt = new BankTransaction("localhost", "ryan", "S!llyb0b1982", "fakeBank");

  int choice;
  int acno;
  std::string fname, lname;
  double bal;

  while (1)
  {
    choice = mainMenu();

    if (choice == END) break;

    switch (choice)
    {
      case PRINT:
        bt->printAllAccount();
        break;
      case NEW:
        std::cout << "\nEnter account no, first name, last name, balance: " << std::endl << "? ";
        std::cin >> acno;
        std::cin >> fname;
        std::cin >> lname;
        std::cin >> bal;

        if (acno < 1)
        {
          std::cout << "Invalid account number." << std::endl;
          break;
        }

        bt->createAccount(new BankAccount(acno, fname, lname, bal));
        break;
      case WITHDRAW:
        std::cout << "\nEnter account no, amount to Withdraw" << std::endl << "? ";
        std::cin >> acno;
        std::cin >> bal;

        if (bal < 0)
        {
          std::cout << "Invalid Amount." << std::endl;
          break;
        }
        
        bt->withdraw(acno, bal);
        break;
      case DEPOSIT:
        std::cout << "\nEnter account no, amount to deposit " << std::endl << "? ";
        std::cin >> acno;
        std::cin >> bal;
        
        if (bal < 0) 
        {
          std::cout << "Invalid amount." << std::endl;
          break;
        }
        
        bt->deposit(acno, bal);
        break;
      case CLOSE:
        std::cout << "\nEnter account number to close account " << std::endl << "? ";
        std::cin >> acno;
        bt->closeAccount(acno);
        break;
      default:
        std::cerr << "Invalid choice!" << std::endl;
        break;
    }
  }

  return 0;
}

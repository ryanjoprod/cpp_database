#include "BankAccount.h"

#include <string>

BankAccount::BankAccount(int accno, std::string fname, std::string lname, double bal)
{
  setAccountNumber(accno);
  setFirstName(fname);
  setLastName(lname);
  setBalance(bal);
}

void BankAccount::setAccountNumber(int accno)
{
  accountNumber = accno;
}

void BankAccount::setLastName(std::string lname)
{
  lastName = lname;
}

void BankAccount::setFirstName(std::string fname)
{
  firstName = fname;
}

void BankAccount::setBalance(double bal)
{
  balance = bal;
}

int BankAccount::getAccountNumber() const
{
  return accountNumber;
}

std::string BankAccount::getFirstName() const
{
  return firstName;
}

std::string BankAccount::getLastName() const
{
  return lastName;
}

double BankAccount::getBalance() const
{
  return balance;
}

BankAccount::~BankAccount() {}

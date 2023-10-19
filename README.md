# C++ Database Programming

I am using this codebase to learn how to program databases with c++, as well as c++ programming in general.  
The original codebase is from [CodeGurus](https://www.codeguru.com/database/database-programming-with-c-c/), and works with the MySQL Connector for c++.  
My version of the program will be using the [MariaDB Connector](https://mariadb.com/downloads/connectors/connectors-data-access/cpp-connector).

## How to use
- run the code in the fakeBank.sql file to create the new database and table
- in `main.cpp` replace `USER` and `PASSWORD` with your database username and password
- compile the program using the following command: `g++ -o fakeBank BankAccount.h BankAccount.cpp BankTransaction.h BankTransaction.cpp main.cpp -std=c++20 -lmariadbcpp`
- to execute the program, use the following command: `./fakeBank`

# C++ Database and Graphics Programming

I am using this codebase to learn how to program databases with c++, as well as c++ programming in general.  

The original codebase is from [CodeGurus](https://www.codeguru.com/database/database-programming-with-c-c/), and works with the MySQL Connector for c++.  

My version of the program will be using the [MariaDB C++ Connector](https://mariadb.com/downloads/connectors/connectors-data-access/cpp-connector).

Main Branch will always follow the most complicated, and up-to-date, branch in the repo.

For the purposes of learning, this repo will only be an executable that is run from the `build` directory, and not an installable program.

## How to use
- run the code in the fakeBank.sql file to create the new database and table
- compile the program using the following command: `mkdir build && cd build && cmake build ../ && cmake --build .`
- to execute the program, use the following command in the `build` directory: `./fakeBank 'USER' 'PASSWORD'`
    - where USER and PASSWORD are the connection details for your MariaDB installation

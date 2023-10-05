CREATE DATABASE IF NOT EXISTS fakeBank;

CREATE TABLE fakeBank.bankAccount (
  accountNumber INT(11) unsigned NOT NULL AUTO_INCREMENT,
  firstName VARCHAR(11) NOT NULL,
  lastName VARCHAR(11) NOT NULL,
  balance DOUBLE NOT NULL
)

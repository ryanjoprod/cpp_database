add_library(BankFunctions BankAccount.cpp BankTransaction.cpp)

target_link_libraries(BankFunctions PUBLIC compiler_flags)

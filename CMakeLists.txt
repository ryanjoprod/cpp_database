cmake_minimum_required(VERSION 3.28)
project(fakeBank VERSION 0.2)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

configure_file(src/projectConfig.h.in projectConfig.h)

# MariaDB include
include_directories("/usr/include/mariadb")
add_library(mariadbcpp STATIC IMPORTED)
set_property(TARGET mariadbcpp PROPERTY IMPORTED_LOCATION "/usr/lib/libmariadbcpp.so")

add_subdirectory(src)

add_executable(fakeBank src/main.cpp)

target_link_libraries(fakeBank PUBLIC BankFunctions compiler_flags mariadbcpp)

target_include_directories(fakeBank PUBLIC "${PROJECT_BINARY_DIR}")

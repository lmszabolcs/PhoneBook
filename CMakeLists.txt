cmake_minimum_required(VERSION 3.27)
project(PhoneBook)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(MEMTRACE)
add_compile_definitions()


include_directories(.)

add_library(memtrace STATIC memtrace.cpp)

SET( CMAKE_CXX_FLAGS  " -Wall -Werror")

add_executable(PhoneBook
        gentomb.h
        gtest_lite.h
        main.cpp
        memtrace.cpp
        memtrace.h
        string5.cpp
        string5.h
        phonebook.cpp
        phonebook.hpp
        contact.cpp
        contact.hpp
        name.cpp
        name.hpp
        menu.hpp
        menu.cpp
)

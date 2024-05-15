cmake_minimum_required(VERSION 3.27)
project(PhoneBook)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PhoneBook
        gentomb.h
        gtest_lite.h
        main.cpp
        memtrace.cpp
        memtrace.h
        string5.cpp
        string5.h
        telefonkonyv.h)

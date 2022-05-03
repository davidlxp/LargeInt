cmake_minimum_required(VERSION 3.20)
project(LargeInt)

set(CMAKE_CXX_STANDARD 14)

add_executable(LargeInt main.cpp DList.cpp DList.h DListIterator.cpp DListIterator.h node.h LargeInt.cpp LargeInt.h LargeIntTest.cpp LargeIntTest.h)

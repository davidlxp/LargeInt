# Large Integer Project

- **Programmer:** Xinpeng (David) Liu
- **Date:** 2022-05-02
- **Section:** CSC-331H

The purpose of this project is creating a class named "LargeInt" for storing integers which is larger than the largest integer which c++ can hold.
<br/>The class holds large integer using a linked list. It also overloaded operators to enable mathematical operations between largeInt variables.

## Contents

The following files should be presented in the same folder:
- `LargeInt.h` (header file for defining LargeInt class)
- `LargeInt.cpp` (implementation of LargeInt class)
- `main.cpp` (the driver class)

The following classes should also be included in the folder stated above, because "LargeInt" class used doubly linkedlist for implementation:
- `node.h` (header file of linked list nodes)
- `DList.h` (header file of the doubly linked list class)
- `DList.cpp` (Implementation of the doubly linked list class)
- `DListIterator.h` (header file of an iterator class for doubly linked list)
- `DListIterator.cpp` (implementation of the iterator class)

Lastly, an unit test has been created for testing the LargeInt class. Please also include the following files into the folder:
- `LargeIntTest.h` (header file of a unit test class for testing the performance of LargeInt class)
- `LargeIntTest.cpp` (implementation of the unit test class)
- `TestCases.txt` (include test cases for analyzing)

## Menu Driven Program for Testing

The `main.cpp` provides a menu driven program to test operations between two large integers. It can evaluate mathematical expression that uses:
- Both positive and negative LargeInt. For example, `-123455672342348234728374928323` or `8273498564837687623784628746238`
- Mathematical operators including `+`, `-`, `*`, `/`, `%`
- Comparison operators including `<`, `<=`, `==`, `>=`, `>`

## To add LargeInt class to your own project
Please copy both `LargeInt.h` and `LargeInt.cpp` files to your project. Then include the header file of LargeInt class into your program by:
```
#include "LargeInt.h"
```

## To create LargeInt variable

**Method 1.** Transform a string into LargeInt variable using operator=
```
String str = "-12345";
LargeInt largeInt;
largeInt = str;
```

**Method2.** Passing a string as parameter when instantiate a LargeInt
```
LargeInt largeInt("-12345");
```

## How To Run The Program
To run it locally, please download the files and save them into a folder
- Open terminal and navigate to the project foler
- run command "g++ main.cpp -o main.out" in terminal, and it will generate a "main.out" file in the project folder
- run command "./main.out" in the terminal









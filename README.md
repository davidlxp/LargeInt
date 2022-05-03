# Large Integer Project

- **Programmer:** Xinpeng (David) Liu
- **Date:** 2022-05-02
- **Section:** CSC-331H

The purpose of this project is creating a class named "LargeInt" for storing integers which is larger than the largest integer which c++ can hold.

The class holds large integer using a linked list. It also overloaded operators to enable mathematical operations between largeInt variables.

## To use the LargeInt class in your own project
Please copy both `LargeInt.h` and `LargeInt.cpp` files to your project.__
There are two ways to create a LargeInt variable:

**Method 1.** Transform a string into LargeInt variable using operator=
```
String str = "-12345";
LargeInt largeInt;
largeInt = str;
```

**Method2.** Passing a string as parameter when instantiate a LargeInt**
```
LargeInt largeInt("-12345");
```


The project implement a arithmetic evaluation by using two stacks. It can evaluate mathematical expression that uses:
- Integer Number (positive & negative). For example, `1` or `-9`
- Decimal Number. For example, `4.5` or `.9`
- Operator including `+`, `-`, `*`, `/`
- parenthese `(` and `)` 

## How To Run The Program
To run it locally, please download the files and save them into a folder
- Open terminal and navigate to the project foler
- run command "g++ main.cpp ArithmeticEvaluation.cpp -o main.out" in terminal, and it will generate a "main.out" file in the project folder
- run command "./main.out" in the terminal









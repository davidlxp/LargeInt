/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: May 2, 2022                                                    */
/* Purpose: A unit-test class for large integer                         */
/************************************************************************/

#ifndef LARGEINT_LARGEINTTEST_H
#define LARGEINT_LARGEINTTEST_H

#include <iostream>
#include <vector>
#include <fstream>
#include "LargeInt.h"
using namespace std;

class LargeIntTest {
private:

    /**
     * @Brief Function read all test cases from provided file address and save them
     * to a vector of testcases passed by reference
     */
    void readTestCases(string fileAddress, vector<vector<string> >& testCases);

    /**
     * @Brief Function reads a line of testcases from text file and extract elements from it
     */
    vector<string> readTestLine(string line);

    /**
     * @Brief Function split a text at certain string.
     * @Input "strToSplit" stands for the text to be split. "splitAt" stands
     * for the string pattern where the program should split the string at
     * @Output a vector of strings which split from the text
     * @Example strToSplit = "hey, how are you, I'm good" & splitAt = ","
     * ===> The result is ["hey", "how are you", "I'm good"]
     */
    vector<string> splitString(string strToSplit, string splitAt) const;


    /**
     * @Brief Function implement calculation between two largeInts
     * @Input 2 string representation of large integers and operator
     * @Output The calculated large integer
     */
    LargeInt largeIntCalculation(string& num1, string& num2, string& op);

public:

    /**
     * @Brief Function run all the testcases and print result in console
     * @Input "fileAddress" is the address of the test cases. "showDetail" is a boolean
     * variable indicates showing detailed test case running result or not
     */
    void runTestCases(string fileAddress, bool showDetail);


};


#endif //LARGEINT_LARGEINTTEST_H

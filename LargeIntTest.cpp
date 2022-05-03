/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: May 2, 2022                                                    */
/* Purpose:  Implementation of a unit-test class for large integer     */
/************************************************************************/

#include "LargeIntTest.h"

void LargeIntTest::readTestCases(string fileAddress, vector<vector<string>>& testCases)
{
    string line;                                                        // a line of text
    ifstream file(fileAddress);

    if (file.is_open())
    {
        while (getline(file, line))                              // get all lines
            testCases.push_back(readTestLine(line));
        file.close();
    }
    else
        cout << "Unable to open file";
}

vector<string> LargeIntTest::readTestLine(string line)
{
    vector<string> result;
    vector<string> temp = splitString(line, " ");
    for (string s : temp)
    {
        if (!s.empty())
            result.push_back(s);
    }
    return result;
}

vector<string> LargeIntTest::splitString(string strToSplit, string splitAt) const
{
    vector<string> strPartList;
    int found;                                                          // index where the splitPoint reside
    int len = splitAt.length();                                         // the length of the pattern to split at

    while ((found = strToSplit.find(splitAt)) != string::npos)
    {
        string strPart = strToSplit.substr(0, found);
        strToSplit = strToSplit.substr(found + len);               // renew the string line
        strPartList.push_back(strPart);                                 // Put partial string into vector
    }
    strPartList.push_back(strToSplit);                                  // put last partial string into the vector
    return strPartList;
}

LargeInt LargeIntTest::largeIntCalculation(string& num1, string& num2, string& op)
{
    LargeInt n1(num1);
    LargeInt n2(num2);

    if (op == "+")
        return n1 + n2;
    else if (op == "-")
        return n1 - n2;
    else if (op == "*")
        return n1 * n2;
    else if (op == "/")
        return n1 / n2;
    else if (op == "%")
        return n1 % n2;
}

void LargeIntTest::runTestCases(string fileAddress, bool showDetail)
{
    vector<vector<string>> testCases;                                   // vector for saving all test cases from file
    readTestCases(fileAddress, testCases);                // read all test cases

    int total = testCases.size();                                       // total number of test cases
    int passed = 0;                                                     // track number of test cases passed
    vector<string> passCases;                                           // saving the test cases which passed
    vector<string> errorCases;                                          // saving the test cases didn't pass

    /* running the test cases and record result */
    for (vector<string> t : testCases)
    {
        LargeInt calcResult = largeIntCalculation(t[0],t[2],t[1]);
        LargeInt key(t[3]);

        if (calcResult == key)
        {
            passed++;
            string correct = t[0] + " " + t[1] + " " + t[2] + " = " + t[3]
                           + " <===> Your Result: " + LargeInt::largeIntToString(calcResult);
            passCases.push_back(correct);
        }
        else
        {
            string error = t[0] + " " + t[1] + " " + t[2] + " = " + t[3]
                    + " <===> Your Result: " + LargeInt::largeIntToString(calcResult);
            errorCases.push_back(error);
        }
    }

    /* print the unit test result */
    cout << "\n" << passed << " out of " << total << " tests passed!" << endl;

    if (showDetail)
    {
        if (!errorCases.empty()) {
            cout << "The Error Cases Are:" << endl;
            for (string e: errorCases)
                cout << e << endl;
        }
        cout << endl;
        if (!passCases.empty()) {
            cout << "The Passed Cases Are:" << endl;
            for (string p: passCases)
                cout << p << endl;
        }
    }

}


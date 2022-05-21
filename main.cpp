/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: May 2, 2022                                                 */
/* Purpose: Section for testing the LargeInt program                 */
/*********************************************************************/


#include <iostream>
#include "LargeInt.h"
#include "LargeIntTest.h"
using namespace std;

/**
 * @Brief The function print main menu and receive user choice
 */
int printMenu();

/**
 * @Brief The function remove extra white spaces from a string
 */
string removeExtraSpace(string text);

/**
 * @Brief The function do calculation of two largeInt and print the result
 */
void largeIntCalculation(LargeInt largeInt1, LargeInt largeInt2, string op);

/**
 * @Brief The function do comparison between two largeInts and print the result
 */
void largeIntComparison(LargeInt largeInt1, LargeInt largeInt2, string op);

/**
 * @Brief The function run the main program
 * @Input The address of the test cases text file
 */
void runProgram(string fileAddress);

/**
 * @Brief The function run the test cases
 */
void runTestCases(string fileAddress);


int main() {

    runProgram("../TestCases.txt");

    return 0;
}

int printMenu()
{
    int choice;

    cout << "\nMain Menu:" << endl;
    cout << "1. Use Large Integer Calculator" << endl;
    cout << "2. Compare Two Large Integers" << endl;
    cout << "3. Run Automated Test Cases" << endl;
    cout << "4. Exit The Program" << endl;
    cout << "Please select 1, 2, 3 or 4: ";

    string choiceStr;
    getline(cin, choiceStr);
    choice = stoi(choiceStr);

    return choice;
}

void runProgram(string fileAddress)
{
    cout << "\nWelcome to the Large Integer Calculator!";
    cout << "\nIf you provide me two large integer and an operator, I could calculate for you." << endl;

    cout << "\nPlease follows the rules below when providing an mathematical expression:";
    cout << "\n> Both positive and negative integers are allowed. There are no limit on number of digits in your integer";
    cout << "\n> Only +, -, *, /, % operators are allowed" << endl;

    int choice = printMenu();
    while (choice != 4)
    {
        if (choice == 1 || choice == 2)
        {
            string numStr1;
            string op;
            string numStr2;

            cout << "\n" << "Please enter the 1st number: ";
            getline(cin, numStr1);

            if (choice == 1)
                cout << "Please enter an operator (eg. *): ";
            else
                cout << "Please enter an operator (eg. >): ";
            getline(cin, op);

            cout << "Please enter the 2nd number: ";
            getline(cin, numStr2);

            // remove potential extra spaces from user's input
            numStr1 = removeExtraSpace(numStr1);
            numStr2 = removeExtraSpace(numStr2);
            op = removeExtraSpace(op);

            // generate largeInt out of num strings
            LargeInt largeInt1(numStr1);
            LargeInt largeInt2(numStr2);

            if (choice == 1)                                                // Do largeInt calculation
                largeIntCalculation(largeInt1, largeInt2, op);
            else                                                            // Do largeInt comparison
                largeIntComparison(largeInt1, largeInt2, op);
        }
        else if (choice == 3)
            runTestCases(fileAddress);
        else
        {
            cout<<"\nNumber is not correct. Please look at "
                <<"choices and reenter\n\n";
        }

        choice = printMenu();
    }
}

string removeExtraSpace(string text)
{
    string result;
    for (char c : text)
    {
        if (c == ' ')
            continue;
        else
            result.push_back(c);
    }
    return result;
}

void largeIntCalculation(LargeInt largeInt1, LargeInt largeInt2, string op)
{
    LargeInt result;

    if (op == "+")
        result = largeInt1 + largeInt2;
    else if (op == "-")
        result = largeInt1 - largeInt2;
    else if (op == "*")
        result = largeInt1 * largeInt2;
    else if (op == "/")
        result = largeInt1 / largeInt2;
    else if (op == "%")
        result = largeInt1 % largeInt2;
    else
    {
        cout << "The operator you provided is invalid!" << endl;
        return;
    }

    cout << "Your input is: " << largeInt1 << " " << op << " " << largeInt2 << endl;
    cout << "Calculation result: " << result << "\n" << endl;
}

void largeIntComparison(LargeInt largeInt1, LargeInt largeInt2, string op)
{
    bool result;

    if (op == "<")
        result = largeInt1 < largeInt2;
    else if (op == "<=")
        result = largeInt1 <= largeInt2;
    else if (op == "==")
        result = largeInt1 == largeInt2;
    else if (op == ">=")
        result = largeInt1 >= largeInt2;
    else if (op == ">")
        result = largeInt1 > largeInt2;
    else if (op == "!=")
        result = largeInt1 != largeInt2;
    else
    {
        cout << "The operator you provided is invalid!" << endl;
        return;
    }

    cout << "Your input is: " << largeInt1 << " " << op << " " << largeInt2 << endl;
    cout << "Comparison result: ";
    if (result)
        cout << "TRUE" << "\n" << endl;
    else
        cout << "FALSE" << "\n" << endl;
}

void runTestCases(string fileAddress)
{
    string choice;
    cout << "Do you wanna see detailed test result? (y/n): ";
    getline(cin, choice);

    LargeIntTest T;

    if (choice == "y")
        T.runTestCases(fileAddress, true);
    else
        T.runTestCases(fileAddress, false);
}
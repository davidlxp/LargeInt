/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: April 17, 2022                                                 */
/* Purpose:  An class for storing large integer and conduct operations  */
/************************************************************************/

#ifndef LARGEINT_LARGEINT_H
#define LARGEINT_LARGEINT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "DList.cpp"
using namespace std;

class LargeInt {
private:
    DList<int> numList;           // a doubly linked list for storing large integer
    char sign;                    // a sign indicates whether this is a positive or negative number

    /**
     * @Brief Function converts string to integer and store them in
     * the linked list of largeInt which passed as reference
     */
    friend void assignStrToLargeInt(string numStr, LargeInt& largeInt);

    /**
     * @Brief Function copy values from largeInt to another largeInt
     */
    void copy(const LargeInt& other);

    /**
     * @Brief Function destroy the current largeInt by removing all its value
     */
    void destroy();

    /**
     * @Brief Function adds two largeInt without taking their sign "+/-" into account
     * @Example largeInt1 = -100, largeInt2 = 90 ---> largeInt1 + largeInt2
     * ---> result from this function: 190, instead of -10
     * @Output a string of unsigned number which represent the calculated largeInt
     */
    friend string addLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs);

    /**
     * @Brief Function conduct subtraction between two positive large integers
     * @Example largeInt1 = 100, largeInt2 = 90 ---> largeInt2 - largeInt1
     * ---> result from this function: 10
     * @Output a string of unsigned number which represent the calculated largeInt
     */
    friend string subtractPositiveLargeInt(LargeInt lhs, LargeInt rhs);

    /**
     * @Brief Function checks if a signs (combination of signs from two largeInt)
     * like "+-" is in a vector of signs or not. Vector of signs could be something
     * like {"0+", "+0", "++", "--", ...}
     * @Output return True if the input "signs" is in the "vector of signs"
     */
    bool signsInVec(vector<string>& signsVec, string& signs) const;

public:

    /**
     * @Brief The constructor of LargeInt class
     */
    LargeInt();

    /**
     * @Brief Overloading "operator>>" so we can read large integer
     * from input stream
     */
    friend istream& operator>>(istream& input, LargeInt& largeInt);

    /**
     * @Brief Overloading "operator<<" so we can output value stored
     * in the doubly linked list of large int class to output stream
     */
    friend ostream& operator<<(ostream& output, LargeInt& largeInt);

    /**
     * @Brief 1st version of overloading operator= so that we can assign
     * the value from a string to a largeInt.
     *
     * For example:
     *   LargeInt x;
     *   string str = "145780";
     *   x = str;
     */
    LargeInt& operator=(string& numStr);

    /**
     * @Brief 2nd version of overloading operator= so that we can assign
     * the value from a largeInt to another
     *
     * For example:
     *   LargeInt x;
     *   LargeInt x1;
     *   string str = "145780";
     *   x1 = x = str;
     */
    LargeInt& operator=(const LargeInt& other);

    LargeInt operator+(const LargeInt& other) const;

    LargeInt operator-(const LargeInt& other) const;

    LargeInt operator*(const LargeInt& other) const;

    LargeInt operator/(const LargeInt& other) const;

    LargeInt operator%(const LargeInt& other) const;


    bool operator==(const LargeInt& other) const;

    bool operator<(const LargeInt& other) const;

    bool operator<=(const LargeInt& other) const;

    bool operator>(const LargeInt& other) const;

    bool operator>=(const LargeInt& other) const;




};


#endif //LARGEINT_LARGEINT_H

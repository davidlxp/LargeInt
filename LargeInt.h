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
     * @Output a positive (+) largeInt which represent the calculation result
     */
    friend LargeInt addLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs);

    /**
     * @Brief Function conduct subtraction between two positive largeInts
     * @Example largeInt1 = 90, largeInt2 = 100 ---> largeInt1 - largeInt2
     * ---> result from this function: -10
     * @Output a signed (+ or -) largeInt which represent the subtraction value between
     * "lhs" and "rhs" largeInts
     */
    friend LargeInt subtractPositiveLargeInt(LargeInt lhs, LargeInt rhs);

    /**
     * @Brief Function multiply two largeInt without taking their sign "+/-" into account
     * @Example largeInt1 = -100, largeInt2 = 90 ---> largeInt1 * largeInt2
     * ---> result from this function: 9000, instead of -9000
     * @Output a positive largeInt which represent the multiplication result
     */
    friend LargeInt multiLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs);

    /**
     * @Brief Function divide a largeInt by another largeInt, without taking
     * their sign "+/-" into account
     * @Example largeInt1 = -100, largeInt2 = 90 ---> largeInt1 / largeInt2
     * ---> result from this function: 1, instead of -1
     * @Output a positive largeInt which represent the multiplication result
     */
    friend LargeInt divideLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs);

    /**
     * @Brief Function checks if a signs (combination of signs from two largeInt)
     * like "+-" is in a vector of signs or not. Vector of signs could be something
     * like {"0+", "+0", "++", "--", ...}
     * @Output return True if the input "signs" is in the "vector of signs"
     */
    bool static signsInVec(vector<string>& signsVec, string& signs);

    /**
     * @Brief Function removes all leading zeros from a "string representation of number"
     * @Detail for example, number "000789" --> after removing will be come "789"
     * @Input the reference of string representation of a number which the user
     * want to remove all of its leading zeros
     */
    void static removeLeadingZeros(string& strNum);

    /**
     * @Brief Function multiplies a largeInt with a integer digit like "6", "8"
     * @Input the positive largeInt and positive single digit int we want to multiply
     * @Output a positive largeInt as the representation of multiplication result
     */
    friend LargeInt multiPosLargeIntWithIntDigit(LargeInt& largeInt, int d);

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

    /**
     * @Brief Overloading "operator+" for user to conduct addition
     * between two largeInt
     * @Input the reference of another largeInt to add with
     * @Output the addition result in LargeInt datatype
     */
    LargeInt operator+(const LargeInt& other) const;

    /**
     * @Brief Overloading "operator-" for user to conduct subtraction
     * between two largeInt
     * @Input the reference of another largeInt to minus with
     * @Output the minus result in LargeInt datatype
     */
    LargeInt operator-(const LargeInt& other) const;

    /**
     * @Brief Overloading "operator*" for user to conduct multiplication
     * between two largeInt
     * @Input the reference of another largeInt to multiply with
     * @Output the multiplication result in LargeInt datatype
     */
    LargeInt operator*(const LargeInt& other) const;

    /**
     * @Brief Overloading "operator*" for user to conduct multiplication
     * between a largeInt and a integer
     * @Input the reference of an integer to multiply with
     * @Output the multiplication result in LargeInt datatype
     */
    LargeInt operator*(const int& other) const;

    /**
     * @Brief Overloading "operator/" for user to conduct division
     * between two largeInt
     * @Input the reference of an integer to divide with
     * @Output the division result in LargeInt datatype
     */
    LargeInt operator/(const LargeInt& other) const;

    /**
     * @Brief Overloading "operator%" for user to conduct module
     * between two largeInt
     * @Input the reference of an integer to module with
     * @Output the division result in LargeInt datatype
     */
    LargeInt operator%(const LargeInt& other) const;

    /**
     * @Brief Overloading comparing symbols for user to conduct
     * comparison between largeInt
     */
    bool operator==(const LargeInt& other) const;
    bool operator!=(const LargeInt& other) const;
    bool operator<(const LargeInt& other) const;
    bool operator<=(const LargeInt& other) const;
    bool operator>(const LargeInt& other) const;
    bool operator>=(const LargeInt& other) const;




};


#endif //LARGEINT_LARGEINT_H

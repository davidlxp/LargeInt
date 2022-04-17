/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: April 17, 2022                                                 */
/* Purpose:  The implementation of LargeInt class                       */
/************************************************************************/

#include "LargeInt.h"

LargeInt::LargeInt()
{
    sign = '\0';
}

void stringToLargeInt(string& numStr, LargeInt& largeInt)
{
    largeInt.destroy();                                     // remove all existing value in largeInt

    if (numStr.length() == 0)                               // don't need to transform string if its empty
        return;
    else if (numStr[0] == '-')                              // try to read number sign (+/-) from the index 0 of input
    {
        largeInt.sign = '-';
        numStr = numStr.substr(1,numStr.length());     // remove 1st element from string b/c it's a sign
    }
    else if (numStr != "0")
        largeInt.sign = '+';                                // sign when number is positive
    else
        largeInt.sign = '0';                                // sign when number is zero

    for (char x : numStr)                                   // insert integer from input into linked list
        largeInt.numList.insertFront(x - '0');         // we can get integer number by doing ('char of num' - '0')
}

void LargeInt::copy(const LargeInt& other)
{
    sign = other.sign;
    numList = other.numList;
}

void LargeInt::destroy()
{
    DList<int> emptyList;
    numList = emptyList;
    sign = '\0';
}

string addLargeIntIgnoreSign(const LargeInt& lhs, const LargeInt& rhs)
{
    string resStr;                                                  // string representation of result largeInt

    int carry = 0;                                                  // variable stores "carry" for each round of calc
    DListIterator<int> frontIterator1 = lhs.numList.begin();        // front iterator of lhs largeInt in addition
    DListIterator<int> frontIterator2 = rhs.numList.begin();        // front iterator of rhs largeInt in addition

    while (!frontIterator1.isNull() || !frontIterator2.isNull())    // continue until both iterator are null
    {
        int val1 = 0;                                               // value pointed by iterator on "this" largeInt
        int val2 = 0;                                               // value pointed by iterator on "other" largeInt
        int keep;                                                   // the value to keep after addition (remove mod)

        if (!frontIterator1.isNull())                               // assign "val" if iterator not points to nullptr
            val1 = frontIterator1.getItem();
        if (!frontIterator2.isNull())
            val2 = frontIterator2.getItem();

        int sum = val1 + val2 + carry;                              // calculate result
        carry = 0;                                                  // reset carry back to 0

        if (sum - 9 <= 0)                                           // if sum <= 9, it won't generate carry
            keep = sum;
        else                                                        // if sum >= 10, it will generate carry
        {
            keep = sum - 10;
            carry = 1;
        }

        resStr = to_string(keep) + resStr;                          // save the calculated value to string

        if (!frontIterator1.isNull())                               // move iterators forward
            frontIterator1.next();
        if (!frontIterator2.isNull())
            frontIterator2.next();
    }

    if (carry == 1)                                                 // the remainder carry 1 means one more digit
        resStr = "1" + resStr;

    return resStr;
}

//string minusLargeIntIgnoreSign(const LargeInt& lhs, const LargeInt& rhs)
//{
//
//}

istream& operator>>(istream &input, LargeInt& largeInt)
{
    string numStr;                                          // a string of number which read from input stream
    input >> numStr;                                        // read from input stream

    stringToLargeInt(numStr, largeInt);              // transform string to largeInt

    return input;
}

ostream& operator<<(ostream &output, LargeInt& largeInt)
{
    // a back iterator to read number from the linked list
    DListIterator<int> backIterator = largeInt.numList.end();

    // attach the number sign "+/-" if any
    if (largeInt.sign == '-')
        output << '-';

    // iterator gets value of largeInt & pass to output
    while (!backIterator.isNull())
    {
        output << backIterator.getItem();
        backIterator.prev();
    }

    return output;
}

LargeInt& LargeInt::operator=(string& numStr)
{
    stringToLargeInt(numStr, *this);
    return *this;
}

LargeInt& LargeInt::operator=(const LargeInt& other)
{
    copy(other);
    return *this;
}

LargeInt LargeInt::operator+(const LargeInt& other) const
{
    string resStr = addLargeIntIgnoreSign(*this, other);
    LargeInt resLargeInt;
    resLargeInt = resStr;

    return resLargeInt;
}

bool LargeInt::operator==(const LargeInt& other) const
{
    // largeInts must have same "+/-" sign and same length to be equal
    if (sign != other.sign || numList.getLength() != other.numList.getLength())
        return false;
    // comparison two largeInts in detail to see if they are equal
    else
    {
        // get back iterators of this and other largeInt
        DListIterator<int> backIterator1 = numList.end();
        DListIterator<int> backIterator2 = other.numList.end();

        // compare int stored in the linked list of this and other largeInt one-by-one
        while (!backIterator1.isNull() && backIterator1.getItem() == backIterator2.getItem())
        {
            backIterator1.prev();
            backIterator2.prev();
        }

        // iterator.isNull means compared all int in two largeInts, and they are all equal. So two largeInts are equal
        if (backIterator1.isNull())
            return true;
        else
            return false;
    }
}

bool LargeInt::operator<(const LargeInt &other) const
{
    string signs;                                               // save combination of sign from this and other
    signs.push_back(sign);
    signs.push_back(other.sign);

    int thisDigits = numList.getLength();                       // get number of digits of both largeInt
    int otherDigits = other.numList.getLength();

    if (other.sign == '\0' || signs == "0-" || signs == "+-")   // if this is 0 or positive and other is negative
        return false;
    else if (signs == "0+" || signs == "-+")                    // if this is 0 or negative and other is positive
        return true;
    else if (thisDigits < otherDigits)
    {
        if (signs == "++")                                      // if this is shorter than other and both positive
            return true;
        else                                                    // if this is shorter than other and both negative
            return false;
    }
    else if (thisDigits > otherDigits)
    {
        if (signs == "++")                                      // if this is longer than other and both positive
            return false;
        else                                                    // if this is longer than other and both negative
            return true;
    }
    else                                                        // if this and other has equal length
    {
        DListIterator<int> backIterator1 = numList.end();
        DListIterator<int> backIterator2 = other.numList.end();

        bool smaller = false;                                   // bool var records whether this is smaller than other
        while (!backIterator1.isNull())
        {
            int val1 = backIterator1.getItem();
            int val2 = backIterator2.getItem();

            if (val1 == val2)                                   // skip to next if digits are the same
            {
                backIterator1.prev();
                backIterator2.prev();
            }
            else if (val1 < val2)                               // if digit from "this" is smaller than that of "other"
            {
                smaller = true;
                break;
            }
            else                                                // if digit from "this" is greater than that of "other"
                break;
        }

        if (backIterator1.isNull())                             // means "this" and "other" are exactly same largeInt
            return false;

        if (signs == "++")                                      // when both largeInt numbers are positive
            return smaller;
        else                                                    // when both largeInt numbers are negative
            return !smaller;
    }
}

bool LargeInt::operator<=(const LargeInt& other) const
{
    return (*this == other || *this < other);
}

bool LargeInt::operator>(const LargeInt& other) const
{
    return (!(*this <= other));
}

bool LargeInt::operator>=(const LargeInt& other) const
{
    return (!(*this < other));
}








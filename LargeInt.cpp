/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: April 17, 2022                                                 */
/* Purpose:  The implementation of LargeInt class                       */
/************************************************************************/

#include "LargeInt.h"

LargeInt::LargeInt()
{
    sign = '+';
}

void stringToLargeInt(string& numStr, LargeInt& largeInt)
{
    if (numStr[0] == '-')                                   // try to read number sign (+/-) from the index 0 of input
    {
        largeInt.sign = '-';
        numStr = numStr.substr(1,numStr.length());     // remove 1st element from string b/c it's a sign
    }

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
    sign = '+';
}

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
    destroy();
    stringToLargeInt(numStr, *this);
    return *this;
}

LargeInt& LargeInt::operator=(const LargeInt& other)
{
    copy(other);
    return *this;
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

//bool LargeInt::operator<(const LargeInt &other) const
//{
//    LargeInt diff = *this - other;
//    if (diff.sign == '-')
//        return true;
//    else
//        return false;
//}






/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: April 17, 2022                                                 */
/* Purpose:  The implementation of LargeInt class                       */
/************************************************************************/

#include "LargeInt.h"

LargeInt::LargeInt()
{
    // Every LargeInt will be initialized as 0
    sign = '0';
    numList.insertFront(0);
}

void assignStrToLargeInt(string numStr, LargeInt& largeInt)
{
    largeInt.destroy();                                     // remove all existing value in largeInt

    if (numStr.length() == 0 || numStr == "0" || numStr == "+0" || numStr == "-0")
    {
        largeInt.sign = '0';                                // read both empty and "0" input as 0
        numStr = "0";
    }
    else if (numStr[0] == '-')                              // try to read number sign "-" from the index 0 of input
    {
        largeInt.sign = '-';
        numStr = numStr.substr(1,numStr.length());     // remove 1st element from string b/c it's a sign
    }
    else if (numStr[0] == '+')                              // try to read number sign "+" from the index 0 of input
    {
        largeInt.sign = '+';
        numStr = numStr.substr(1,numStr.length());     // remove 1st element from string b/c it's a sign
    }
    else
    {
        largeInt.sign = '+';                                // sign when number is positive
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
    sign = '\0';
}

string addLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs)
{
    string resStr;                                                  // string representation of result largeInt

    int carry = 0;                                                  // variable stores "carry" for each round of calc
    DListIterator<int> frontIterator1 = lhs.numList.begin();        // front iterator of lhs largeInt in addition
    DListIterator<int> frontIterator2 = rhs.numList.begin();        // front iterator of rhs largeInt in addition

    while (!frontIterator1.isNull() || !frontIterator2.isNull())    // continue until both iterator are null
    {
        int val1 = 0;                                               // value pointed on linked list of "lhs" largeInt
        int val2 = 0;                                               // value pointed on linked list of "rhs" largeInt
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

string subtractPositiveLargeInt(LargeInt lhs, LargeInt rhs)
{
    // variable records if the position of two largeInt swapped
    bool swap = false;

    // if lhs is smaller than the rhs, swap them, so we always have large value minus smaller
    if (lhs < rhs)
    {
        LargeInt temp = rhs;
        rhs = lhs;
        lhs = temp;
        swap = true;
    }

    // the front iterators of linked list in two largeInt variables
    string resStr;                                                  // string representation of result largeInt
    int borrow = 0;                                                 // variable stores value borrowed from higher digit
    DListIterator<int> frontIterator1 = lhs.numList.begin();        // front iterator of lhs largeInt in addition
    DListIterator<int> frontIterator2 = rhs.numList.begin();        // front iterator of rhs largeInt in addition

    while (!frontIterator1.isNull() || !frontIterator2.isNull())    // continue until both iterator are null
    {
        int val1 = 0;                                               // value pointed on linked list of "lhs" largeInt
        int val2 = 0;                                               // value pointed on linked list of "rhs" largeInt

        if (!frontIterator1.isNull())                               // assign "val" if iterator not points to nullptr
            val1 = frontIterator1.getItem();
        if (!frontIterator2.isNull())
            val2 = frontIterator2.getItem();

        val1 -= borrow;                                             // deduct borrowed value from last round
        if (val1 < val2)
        {
            borrow = 1;                                             // borrow value from higher digit
            val1 += 10;
        }
        int sub = val1 - val2;                                      // calculate result

        resStr = to_string(sub) + resStr;                           // save the calculated value to string

        if (!frontIterator1.isNull())                               // move iterators forward
            frontIterator1.next();
        if (!frontIterator2.isNull())
            frontIterator2.next();
    }

    // if the most significant digit of result is "0", it's been borrowed to empty during calculation, remove it
    if (resStr[0] == '0')
        resStr = resStr.substr(1, resStr.length());

    // "str" is a helper string which helps with checking if the result string is consisted all by "0"
    string str = resStr;
    str.erase(remove(str.begin(), str.end(), '0'), str.end());

    // return the final subtraction result
    if (str.empty())                                                // if result is all "0" like "00000...", return "0"
        return "0";
    else if (swap)                                                  // if lhs and rhs swapped before subtraction
        return ("-" + resStr);
    else                                                            // if lhs and rhs didn't swap before subtraction
        return resStr;
}

bool LargeInt::signsInVec(vector<string>& signsVec, string& signs) const
{
    if (count(signsVec.begin(), signsVec.end(), signs))
        return true;
    else
        return false;
}

istream& operator>>(istream &input, LargeInt& largeInt)
{
    string numStr;                                                 // a string of number which read from input stream
    input >> numStr;                                               // read from input stream

    largeInt = numStr;                                             // assign the input string to largeInt

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
    assignStrToLargeInt(numStr, *this);
    return *this;
}

LargeInt& LargeInt::operator=(const LargeInt& other)
{
    copy(other);
    return *this;
}

LargeInt LargeInt::operator+(const LargeInt& other) const
{
    string signs;                                               // save combination of sign from this and other
    signs.push_back(sign);
    signs.push_back(other.sign);

    string resStr;                                              // string representation of a largeInt
    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    if (signs == "00")
        resStr = "0";
    else if (signs == "0+" || signs == "+0" || signs == "++")
        resStr = addLargeIntIgnoreSign(*this, other);
    else if (signs == "0-" || signs == "-0" || signs == "--")
    {
        resStr = addLargeIntIgnoreSign(*this, other);  // -90 & -60 ==> (90 + 60) ==> return "150"
        resStr = "-" + resStr;                                  // add "-" before "150" ==> "-150"
    }
    else                                                        // when signs == "+-" or "-+"
    {
        if (sign == '-')                                        // if "this" is the negative one
        {
            LargeInt newThis(*this);
            newThis.sign = '+';
            return other - newThis;                             // eg. -90 + 60 == 60 - 90
        }
        else                                                    // if "other" is the negative one
        {
            LargeInt newOther(other);
            newOther.sign = '+';
            return *this - newOther;                            // eg. 90 + (-60) == 90 - 60
        }
    }

    resLargeInt = resStr;                                       // str to largeInt. eg. "-150" ==> 0->1->5, sign = '-'
    return resLargeInt;
}

LargeInt LargeInt::operator-(const LargeInt& other) const
{
    string signs;                                               // save combination of sign from this and other
    signs.push_back(sign);
    signs.push_back(other.sign);

    string resStr;                                              // string representation of a largeInt
    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    if (signs == "00")                                          // when 0 - 0, return 0
    {
        resStr = "0";
        resLargeInt = resStr;
    }
    else if (signs == "0+" || signs == "0-")                    // when "0 - positive num" or "0 - negative num"
    {
        resLargeInt = other;                                    // the result is "other" largeInt with its sign reversed
        if (signs == "0+")
            resLargeInt.sign = '-';
        else
            resLargeInt.sign = '+';
    }
    else if (signs == "+0" || signs == "-0")                    // when "positive num - 0" or "negative num - 0"
        resLargeInt = *this;                                    // the result is "this" largeInt
    else if (signs == "-+" || signs == "+-" || signs == "--")
    {
        LargeInt posThis = *this;                               // turning both "this" and "other" to positive
        LargeInt posOther = other;
        posThis.sign = '+';
        posOther.sign = '+';

        if (signs == "-+" || signs == "+-")                     // eg of "-+" ==>  -9 - 8   ==> -(9 + 8)
        {                                                       // eg of "+-" ==>  9 - (-8) ==> 9 + 8
            resLargeInt = posThis + posOther;
            if (signs == "-+")
                resLargeInt.sign = '-';
        }
        else                                                    // eg of "--" ==> -9 - (-8) ==> 8 - 9
        {
            // swap position of the positive version of "this" and "other" before subtraction
            resStr = subtractPositiveLargeInt(posOther, posThis);
            resLargeInt = resStr;
        }
    }
    else                                                        // when doing subtraction of two positive numbers
    {   // do subtraction for positive version of "this" and "other"
        resStr = subtractPositiveLargeInt(*this, other);
        resLargeInt = resStr;
    }

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

    vector<string> defNotSmallerSigns {"00", "0-", "+-", "+0"};
    vector<string> defSmallerSigns {"-0", "0+", "-+"};

    int thisDigits = numList.getLength();                       // get number of digits of both largeInt
    int otherDigits = other.numList.getLength();

    if (signsInVec(defNotSmallerSigns, signs))            // if this is 0 or positive and other is negative
        return false;
    else if (signsInVec(defSmallerSigns, signs))          // if this is 0 or negative and other is positive
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








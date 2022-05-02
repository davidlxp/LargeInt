/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: May 2, 2022                                                    */
/* Purpose:  The implementation of LargeInt class                       */
/************************************************************************/

#include "LargeInt.h"

LargeInt::LargeInt()
{
    // Every LargeInt will be initialized as 0
    sign = '0';
    numList.insertFront(0);
}

LargeInt::LargeInt(string numStr)
{
    assignStrToLargeInt(numStr, *this);
}

void LargeInt::assignStrToLargeInt(string numStr, LargeInt& largeInt)
{
    largeInt.destroy();                                     // remove all existing value in largeInt

    if (numStr.empty())                                     // if string is empty, then we assume input value is "0"
    {
        largeInt.sign = '0';
        numStr = "0";
    }
    else
    {
        char sign = '\0';                                    // variable for storing the sign from numStr (if any)

        if (!isdigit(numStr[0]))                         // if 1st item from numStr is not digit, like "-7", "*8"
        {
            sign = numStr[0];                                // save the sign
            numStr = numStr.substr(1, numStr.length()); // remove 1st element from string b/c it's a sign
        }

        LargeInt::removeLeadingZeros(numStr);             // remove leading zeros if any (eg. 0020 --> 20)

        if (numStr.empty())                                  // string becomes empty, then the input value is "0..."
        {
            largeInt.sign = '0';
            numStr = "0";
        }
        else if (sign == '-' || sign == '+')                 // if string is not yet empty, input contains + or -
            largeInt.sign = sign;
        else                                                 // if string is not yet empty, input doesn't have + or -
            largeInt.sign = '+';
    }

    for (char x : numStr)                                    // insert integer from input into linked list
        largeInt.numList.insertFront(x - '0');          // we can get integer number by doing ('char of num' - '0')
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

LargeInt LargeInt::addLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs)
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

        resStr = to_string(keep).append(resStr);                    // save the calculated value to string

        if (!frontIterator1.isNull())                               // move iterators forward
            frontIterator1.next();
        if (!frontIterator2.isNull())
            frontIterator2.next();
    }

    if (carry == 1)                                                 // the remainder carry 1 means one more digit
        resStr = "1" + resStr;

    LargeInt resLargeInt;                                           // result largeInt to be returned
    resLargeInt = resStr;
    return resLargeInt;
}

LargeInt LargeInt::subtractPositiveLargeInt(LargeInt lhs, LargeInt rhs)
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
        borrow = 0;                                                 // reset borrow to zero

        if (val1 < val2)
        {
            borrow = 1;                                             // borrow value from higher digit
            val1 += 10;
        }
        int sub = val1 - val2;                                      // calculate result

        resStr = to_string(sub).append(resStr);                     // save the calculated value to string

        if (!frontIterator1.isNull())                               // move iterators forward
            frontIterator1.next();
        if (!frontIterator2.isNull())
            frontIterator2.next();
    }

    // remove leading zeros from result. eg: 1. "0007" --> "7", "00" --> ""
    LargeInt::removeLeadingZeros(resStr);

    // return the final subtraction result
    if (resStr.empty())                                             // if result is all "0" like "00000...", return "0"
        resStr = "0";
    else if (swap)                                                  // if lhs and rhs swapped before subtraction
        resStr = "-" + resStr;

    LargeInt resLargeInt;                                           // result largeInt to be returned
    resLargeInt = resStr;
    return resLargeInt;
}

LargeInt LargeInt::multiLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs)
{
    string resStr;
    DListIterator<int> frontIteratorR = rhs.numList.begin();        // the front iterator of the largeInt "rhs"

    LargeInt resLargeInt;                                           // the largeInt as a result to be returned
    int extraZeroNum = 0;                                           // num of extra zeros needed to add to temp result

    while (!frontIteratorR.isNull())
    {
        int digit = frontIteratorR.getItem();                       // a digit from largeInt rhs

        // let one digit from "rhs" multi largeInt "lhs", and save temp multi result to a temp largeInt
        LargeInt tempLargeInt = multiLargeIntIgnoreSignWithPosIntDigit(lhs, digit);

        // adding extra "0" to the temp multi result
        for (int i=0; i<extraZeroNum; ++i)
            tempLargeInt.numList.insertFront(0);
        extraZeroNum++;                                             // increment the "extraZeroNum" for next round

        // update the result largeInt after a round of calculation
        resLargeInt = resLargeInt + tempLargeInt;

        // move the iterator forward
        frontIteratorR.next();
    }

    return resLargeInt;
}

LargeInt LargeInt::multiLargeIntIgnoreSignWithPosIntDigit(LargeInt& largeInt, int d)
{
    string resStr;                                                  // string representation of result largeInt
    DListIterator<int> frontIterator = largeInt.numList.begin();    // the front iterator of the largeInt

    int carry = 0;                                                  // the carry after a round of multiplication

    while (!frontIterator.isNull())
    {
        int val = frontIterator.getItem();                          // value pointed on linked list of largeInt
        int keep;                                                   // the value to keep after multiplication

        int multi = val * d + carry;                                // conduct the multiplication
        carry = 0;                                                  // reset the carry to 0

        if (to_string(multi).length() == 1)                         // if multi result has no carry (eg. 1*6 = 6)
            keep = multi;
        else                                                        // if multi result has carry (eg. 7*6 = 42)
        {
            keep = to_string(multi)[1] - '0';                       // value to keep in this digit (eg. 42 -> keep = 2)
            carry = to_string(multi)[0] - '0';                      // value to keep in this digit (eg. 42 -> keep = 4)
        }

        resStr = to_string(keep).append(resStr);                    // adding keep value to result string

        frontIterator.next();                                       // move the iterator to next
    }

    if (carry != 0)
        resStr = to_string(carry).append(resStr);                   // adding carry to result string if carry is not 0

    LargeInt resLargeInt;                                           // the result largeInt of calculation
    resLargeInt = resStr;
    resLargeInt.sign = '+';

    return resLargeInt;
}

LargeInt LargeInt::divideLargeIntIgnoreSign(LargeInt lhs, LargeInt rhs)
{
    lhs.sign = '+';                                                 // turning both largeInt to positive
    rhs.sign = '+';

    string resStr;                                                  // string representation of result largeInt
    DListIterator<int> backIteratorL = lhs.numList.end();           // the end iterator of the largeInt lhs

    LargeInt tempNumerator;                                         // temp numerator will iteratively divide rhs

    while (!backIteratorL.isNull())
    {
        // a variable indicates whether it's the beginning of the round
        bool roundBeginFlag = true;

        // add value to temp numerator until it >= largeInt rhs
        while (tempNumerator < rhs && !backIteratorL.isNull())
        {
            // add zero to final calculation string if it is not empty, and it's not the beginning of round
            if (!resStr.empty() && !roundBeginFlag)
                resStr.append(to_string(0));

            // update the round begin flag to indicate it's not the beginning of round anymore
            if (roundBeginFlag)
                roundBeginFlag = false;

            // if temporary numerator is zero, empty its linked list to prepare for loading.
            if (tempNumerator.sign == '0')
            {
                tempNumerator.destroy();
                tempNumerator.sign = '+';
            }

            // get one digit from largeInt "lhs" and insert to tempNumerator
            int val = backIteratorL.getItem();
            backIteratorL.prev();
            tempNumerator.numList.insertFront(val);
        }

        // if the tempNumerator >= rhs, do division.
        // if tempNumerator < rhs, but iterator is null, it means the division process end
        if (tempNumerator >= rhs)
        {
            // rhs is the denominator. Multiply it by 1...9, until find the largest value which is
            // smaller than the tempNumerator. And that value is the division result of this round.
            int i = 1;
            while (rhs * i <= tempNumerator)
                i++;
            resStr.append(to_string(i-1));

            // after get division result for this round. Prepare tempNumerator for the next round
            tempNumerator = tempNumerator - rhs * (i-1);
        }
    }

    LargeInt resLargeInt;                                           // the result largeInt of calculation
    resLargeInt = resStr;
    resLargeInt.sign = '+';

    return resLargeInt;
}

bool LargeInt::signsInVec(vector<string>& signsVec, string& signs)
{
    if (count(signsVec.begin(), signsVec.end(), signs))
        return true;
    else
        return false;
}

void LargeInt::removeLeadingZeros(string& strNum)
{
    int i = 0;                                                     // index where the 1st non-zero int appear in string

    while (strNum[i] - '0' == 0)                                   // find the smallest index which is not zero
        i++;

    strNum = strNum.substr(i, strNum.length());                    // get the string part that does not have leading 0
}

LargeInt LargeInt::integerToLargeInt(const int& integer)
{
    // create largeInt representation for an integer
    string intStr = to_string(integer);
    LargeInt largeInt;
    largeInt = intStr;
    return largeInt;
}

string LargeInt::combineSigns(const LargeInt& lhs, const LargeInt& rhs)
{
    string signs;                                                  // save combination of sign from this and other
    signs.push_back(lhs.sign);
    signs.push_back(rhs.sign);
    return signs;
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

LargeInt& LargeInt::operator=(const int& other)
{
    // create largeInt representation for an integer
    string otherNumStr = to_string(other);
    assignStrToLargeInt(otherNumStr, *this);
    return *this;
}

LargeInt LargeInt::operator+(const LargeInt& other) const
{
    string signs = LargeInt::combineSigns(*this, other);   // combination of sign from this and other

    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    if (signs == "00")
    {
        string tempStr = "0";
        resLargeInt = tempStr;
    }
    else if (signs == "0+" || signs == "+0" || signs == "++")
        resLargeInt = addLargeIntIgnoreSign(*this, other);
    else if (signs == "0-" || signs == "-0" || signs == "--")
    {
        // -90 & -60 ==> (90 + 60) ==> return "150"
        resLargeInt = addLargeIntIgnoreSign(*this, other);
        resLargeInt.sign = '-';                                 // convert the result largeInt to negative
    }
    else                                                        // when signs is "+-" or "-+"
    {
        if (sign == '-')                                        // if "this" is the one which is negative
        {
            LargeInt newThis(*this);
            newThis.sign = '+';
            resLargeInt = other - newThis;                      // eg. -90 + 60 == 60 - 90
        }
        else                                                    // if "other" is the negative one
        {
            LargeInt newOther(other);
            newOther.sign = '+';
            resLargeInt = *this - newOther;                     // eg. 90 + (-60) == 90 - 60
        }
    }

    return resLargeInt;
}

LargeInt LargeInt::operator-(const LargeInt& other) const
{
    string signs = LargeInt::combineSigns(*this, other);   // combination of sign from this and other

    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    if (signs == "00")                                          // when 0 - 0, return 0
    {
        string tempStr;
        tempStr = "0";
        resLargeInt = tempStr;
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
            // swap position of the positive version of "this" and "other" before subtraction
            resLargeInt = subtractPositiveLargeInt(posOther, posThis);
    }
    else                                                        // when doing subtraction of two positive numbers
        // do subtraction for "this" and "other" largeInt, both of them are positive
        resLargeInt = subtractPositiveLargeInt(*this, other);

    return resLargeInt;
}

LargeInt LargeInt::operator*(const LargeInt& other) const
{
    string signs = LargeInt::combineSigns(*this, other);   // combination of sign from this and other

    string resStr;                                              // string representation of a largeInt
    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    // sign combination indicates the result should be zero, positive or negative
    vector<string> resultIsZeroSigns {"00", "0-", "-0", "0+", "+0"};
    vector<string> resultIsPosSigns {"++", "--"};
    vector<string> resultIsNegSigns {"+-", "-+"};

    if (signsInVec(resultIsZeroSigns, signs))            // if multiplication result should be zero
        resLargeInt = LargeInt("0");
    else if (signsInVec(resultIsPosSigns, signs))        // if multiplication result should be positive
    {
        resLargeInt = multiLargeIntIgnoreSign(*this, other);
        resLargeInt.sign = '+';
    }
    else                                                        // if multiplication result should be negative
    {
        resLargeInt = multiLargeIntIgnoreSign(*this, other);
        resLargeInt.sign = '-';
    }

    return resLargeInt;
}

LargeInt LargeInt::operator/(const LargeInt& other) const
{
    string signs = LargeInt::combineSigns(*this, other);   // combination of sign from this and other

    string resStr;                                              // string representation of a largeInt
    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    // sign combination indicates the result should be zero, positive or negative
    vector<string> resultInvalidSigns {"00", "-0", "+0"};
    vector<string> resultIsZeroSigns {"0-", "0+"};
    vector<string> resultIsPosSigns {"++", "--"};
    vector<string> resultIsNegSigns {"+-", "-+"};

    // assert if denominator is zero
    assert(!signsInVec(resultInvalidSigns, signs) && "Operation is invalid. Denominator can NOT be zero!");

    // division operations
    if (signsInVec(resultIsZeroSigns, signs))            // if division result should be zero
        resLargeInt = LargeInt("0");
    else if (signsInVec(resultIsPosSigns, signs))        // if multiplication result should be positive
    {
        resLargeInt = divideLargeIntIgnoreSign(*this, other);
        resLargeInt.sign = '+';
    }
    else                                                        // if multiplication result should be negative
    {
        resLargeInt = divideLargeIntIgnoreSign(*this, other);
        resLargeInt.sign = '-';
    }

    return resLargeInt;
}

LargeInt LargeInt::operator%(const LargeInt& other) const
{
    string signs = combineSigns(*this, other);   // combination of sign from this and other

    string resStr;                                              // string representation of a largeInt
    LargeInt resLargeInt;                                       // the largeInt as a result to be returned

    // sign combination indicates the result should be zero, positive or negative
    vector<string> resultInvalidSigns {"00", "-0", "+0"};
    vector<string> resultIsZeroSigns {"0-", "0+"};
    vector<string> sameSigns {"++", "--"};
    vector<string> diffSigns {"+-", "-+"};

    // assert if denominator is zero
    assert(!signsInVec(resultInvalidSigns, signs) && "Operation is invalid. Denominator of module can NOT be zero!");

    // division operations
    if (signsInVec(resultIsZeroSigns, signs))            // if division result should be zero
        resLargeInt = LargeInt("0");
    else if (signsInVec(sameSigns, signs))               // if two signs are the same like "++" or "--"
    {
        LargeInt quotient = *this / other;                      // firstly divide LargeInt this and other

        if (*this == other * quotient)                          // get the module
            resLargeInt = LargeInt("0");
        else
            resLargeInt = *this - (other * quotient);
    }
    else
    {
        LargeInt quotient = *this / other;                      // firstly divide LargeInt this and other
        if (*this == other * quotient)                          // get the module
            resLargeInt = LargeInt("0");
        else
            resLargeInt = *this - (other * (quotient-1));

    }

    return resLargeInt;
}

LargeInt LargeInt::operator+(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = integerToLargeInt(other);

    // return the addition between two largeInt
    LargeInt resLargeInt = (*this) + otherLargeInt;
    return (resLargeInt);
}

LargeInt LargeInt::operator-(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = LargeInt::integerToLargeInt(other);

    // return the minus between two largeInt
    LargeInt resLargeInt = (*this) - otherLargeInt;
    return (resLargeInt);
}

LargeInt LargeInt::operator*(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = LargeInt::integerToLargeInt(other);

    // return the multiplication between two largeInt
    LargeInt resLargeInt = (*this) * otherLargeInt;
    return (resLargeInt);
}

LargeInt LargeInt::operator/(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = LargeInt::integerToLargeInt(other);

    // return the division between two largeInt
    LargeInt resLargeInt = (*this) / otherLargeInt;
    return (resLargeInt);
}

LargeInt LargeInt::operator%(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = LargeInt::integerToLargeInt(other);

    // return the module between two largeInt
    LargeInt resLargeInt = (*this) % otherLargeInt;
    return (resLargeInt);
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

bool LargeInt::operator!=(const LargeInt &other) const
{
    return (!(*this == other));
}

bool LargeInt::operator<(const LargeInt &other) const
{
    string signs = combineSigns(*this, other);   // combination of sign from this and other

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

bool LargeInt::operator==(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = integerToLargeInt(other);

    return (*this == otherLargeInt);
}

bool LargeInt::operator!=(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = integerToLargeInt(other);

    return (*this != otherLargeInt);
}

bool LargeInt::operator<(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = integerToLargeInt(other);

    return (*this < otherLargeInt);
}

bool LargeInt::operator<=(const int& other) const
{
    // create largeInt representation for an integer
    LargeInt otherLargeInt = integerToLargeInt(other);

    return (*this <= otherLargeInt);
}

bool LargeInt::operator>(const int& other) const
{
// create largeInt representation for an integer
LargeInt otherLargeInt = integerToLargeInt(other);

return (*this > otherLargeInt);
}

bool LargeInt::operator>=(const int& other) const
{
// create largeInt representation for an integer
    LargeInt otherLargeInt = integerToLargeInt(other);

    return (*this >= otherLargeInt);
}










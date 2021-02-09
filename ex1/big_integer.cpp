/**
 * @file big_integer.cpp
 * @author  benm
 * @date 4 sept 2018
 * @section DESCRIPTION
 * Handling very big numbers in strings
 */

// ------------------------------ includes ------------------------------
#include <algorithm>
#include <iostream>
#include "big_integer.h"

using namespace std;

// -------------------------- const definitions -------------------------
#define DEFAULT "0"
#define BASE_ZERO "0"
#define BASE_ONE "1"
#define ZERO_CHAR '0'
#define  MINUS '-'
#define BASE 10


// ------------------------------ functions -----------------------------

/**
 * Clean the zeros at the beginning of a string
 * @param str string to clean
 * @return cleaned string
 */
string &cleanZeros(string &str)
{
    int count = (int) str.length() - 1;

    while (count >= 0 && str[count] == ZERO_CHAR)
    {
        count--;
    }
    str = str.substr(0, (unsigned long) count + 1);
    return str;
}


/**
 * Constructor
 */
big_integer::big_integer() : _number(DEFAULT), _sign(1)
{}

/**
 * Copy constructor
 * @param toCopy toCopy
 */
big_integer::big_integer(const big_integer &toCopy) = default;

/**
 * Constructor
 * @param num value
 */
big_integer::big_integer(int num)
{
    if (num >= 0)
    {
        _sign = 1;

    }
    else
    {
        _sign = -1;
        num = -num;
    }
    _number = to_string(num);
    reverse(_number.begin(), _number.end());
}

/**
 * Constructor
 * @param str value
 */
big_integer::big_integer(string str)
{
    bool valid = true;
    _sign = 1;
    if (str[0] == MINUS)
    {
        _sign = -1;
        str = str.substr(1, str.length() - 1);
    }

    for (char chr:str)
    {
        if (!isdigit(chr))
        {
            valid = false;
            break;
        }
    }
    if (valid)
    {
        reverse(str.begin(), str.end());
        _number = cleanZeros(str);
    }
    else
    {
        _number = DEFAULT;
        _sign = 1;
    }
    if (str.empty())
    {
        _number = DEFAULT;
        _sign = 1;

    }

}

/**
 * A function to know if abs(a)<abs(b)
 * @param a a
 * @param b b
 * @return true iff abs(a)<abs(b)
 */
bool absInf(const string &a, const string &b)
{
    string reversedA = a, reversedB = b;
    reverse(reversedA.begin(), reversedA.end());
    reverse(reversedB.begin(), reversedB.end());
    if (reversedA.length() != reversedB.length())
    {
        return reversedA.length() < reversedB.length();
    }
    for (int i = 0; i < (int) reversedB.length(); i++)
    {
        if (reversedA[i] != reversedB[i])
        {
            return reversedA[i] < reversedB[i];
        }
    }
    return false;

}

/**
 * Operator= for big_integers
 * @param toCopy to assign
 * @return reference to assigned
 */
big_integer &big_integer::operator=(const big_integer &toCopy) = default;

/**
 * Operator << for big_integers
 * @param os stream
 * @param toPrint number to print
 * @return reference to the steam
 */
ostream &operator<<(ostream &os, const big_integer &toPrint)
{
    if (toPrint._sign == -1)
    {
        os << MINUS;
    }
    for (int i = (int) toPrint._number.length() - 1; i >= 0; i--)
    {
        os << toPrint._number[i];
    }
    return os;
}

/**
 * Operator to compare big_integers
 * @param a a
 * @param b b
 * @return true iff
 */
bool operator<(const big_integer &a, const big_integer &b)
{

    return (a._sign < b._sign) ||
           (a._sign == -1 && b._sign == -1 && absInf(b._number, a._number))
           || (a._sign == 1 && b._sign == 1 && absInf(a._number, b._number));

}

/**
 * Operator to compare big_integers
 * @param a a
 * @param b b
 * @return true iff
 */
bool operator>(const big_integer &a, const big_integer &b)
{
    return b < a;
}

/**
 * Operator to compare big_integers
 * @param a a
 * @param b b
 * @return true iff
 */
bool operator<=(const big_integer &a, const big_integer &b)
{ return !(a > b); }

/**
 * Operator to compare big_integers
 * @param a a
 * @param b b
 * @return true iff
 */
bool operator>=(const big_integer &a, const big_integer &b)
{ return !(a < b); }

/**
 * Operator to compare big_integers
 * @param a a
 * @param b b
 * @return true iff
 */
bool operator==(const big_integer &a, const big_integer &b)
{
    return (a._sign == b._sign && a._number == b._number);
}

/**
 * Operator to compare big_integers
 * @param a a
 * @param b b
 * @return true iff
 */
bool operator!=(const big_integer &a, const big_integer &b)
{
    return !(a == b);
}

/**
 * Get a digit from a string
 * @param number string
 * @param i place
 * @return the digit
 */
int getDigit(string number, int i)
{
    if (i < (int)number.length() && i >= 0)
    {
        return (int) ((number)[i] - ZERO_CHAR);
    }
    else
    {
        return 0;
    }
}

/**
 * Get the i first digits as a string
 * @param number number of digits we want
 * @param i index
 * @return string
 */
string getDigits(const string &number, int i)
{
    string result;
    for (int j = (int) number.length() - i; j < (int) number.length(); j++)
    {
        result += number[j];
    }
    return result;
}

/**
 * Function to get the max in absolute value
 * @param a a
 * @param b b
 * @return max
 */
const big_integer &absMax(const big_integer &a, const big_integer &b)
{
    if (absInf(b._number, a._number))
    {
        return a;
    }
    return b;
}

/**
 * Perform an addition on 2 positives numbers, with a>b
 * @param a a
 * @param b b
 * @return result
 */
string positivePlus(const string &a, const string &b)
{
    string result;
    int digit = 0, remain = 0;
    for (int i = 0; i < (int) a.length(); i++)
    {

        digit = getDigit(a, i) + getDigit(b, i) + remain;
        remain = digit / BASE;
        digit = digit % BASE;
        result += to_string(digit);
    }
    if (remain != 0)
    {
        result += to_string(remain);
    }
    return cleanZeros(result);
}

/**
 * Perform a sub on 2 positives numbers, with a>b
 * @param a a
 * @param b b
 * @return result
 */
string positiveMinus(const string &a, const string &b)
{
    string result;
    int digit;
    int remain = 0;
    for (int i = 0; i < (int) a.length(); i++)
    {

        digit = getDigit(a, i) - (getDigit(b, i) + remain);
        if (digit < 0)
        {
            digit += BASE;
            remain = 1;
        }
        else
        {
            remain = 0;
        }
        if (i == (int) a.length() - 1 && digit == 0)
        {
            break;
        }
        result += to_string(digit);
    }
    return cleanZeros(result);
}

/**
 * Addition operator on 2 big_integers
 * @param a a
 * @param b b
 * @return results
 */
big_integer operator+(const big_integer &a, const big_integer &b)
{
    if (absInf(a._number, b._number))
    {
        return b + a; //enforce the order
    }
    big_integer result;
    if (a._sign == b._sign)
    {
        result._sign = a._sign;
        result._number = positivePlus(a._number, b._number);
    }
    else
    {
        result._sign = absMax(a, b)._sign;
        result._number = positiveMinus(a._number, b._number);
    }
    if (result._number.empty() || result._number == BASE_ZERO)
    {
        result._number = DEFAULT;
        result._sign = 1;
    }

    return result;
}

/**
 * Sub operator on 2 big_integers
 * @param a a
 * @param b b
 * @return results
 */
big_integer operator-(const big_integer &a, const big_integer &b)
{
    big_integer result;
    if (b._sign == -1)
    {
        big_integer newB = b;
        newB._sign = 1;
        return a + newB;
    }
    else if (a._sign == b._sign) // 2 positives
    {
        if (a >= b)
        {
            result._sign = 1;
            result._number = positiveMinus(a._number, b._number);
        }
        else
        {
            result._sign = -1;
            result._number = positiveMinus(b._number, a._number);
        }
    }
    else // a negative b positive
    {
        result._sign = -1;
        if (absInf(a._number, b._number))
        {
            result._number = positivePlus(b._number, a._number);
        }
        else
        {
            result._number = positivePlus(a._number, b._number);
        }
    }
    if (result._number.empty() || result._number == BASE_ZERO)
    {
        result._number = DEFAULT;
        result._sign = 1;
    }
    return result;
}

/**
 * += operator for big_integers
 * @param other to add
 * @return reference to the incremented
 */
big_integer &big_integer::operator+=(const big_integer &other)
{
    (*this) = (*this) + other;
    return *this;
}

/**
 * -= operator for big_integers
 * @param other to add
 * @return reference to the decremented
 */
big_integer &big_integer::operator-=(const big_integer &other)
{
    (*this) = (*this) - other;
    return *this;
}

/**
 * Perform a multiplication when the second term has 1 digit, and all positives
 * @param a a positive number
 * @param multDigit a digit
 * @param result result to add on
 * @return product
 */
string &digitMult(const string &a, const int &multDigit, string &result)
{

    int digit = 0, remain = 0;
    for (int i = 0; i < (int) a.length(); i++)
    {
        digit = getDigit(a, i) * multDigit + remain;
        remain = digit / BASE;
        digit = digit % BASE;
        result += to_string(digit);
    }
    if (remain != 0)
    {
        result += to_string(remain);
    }

    return cleanZeros(result);
}

/**
 * Perform multiplication on two big_integers
 * @param a a
 * @param b b
 * @return product
 */
big_integer operator*(const big_integer &a, const big_integer &b)
{
    big_integer result, temp;

    for (int i = 0; i < (int) b._number.length(); i++)
    {
        string compute;
        for (int j = 0; j < i; j++)
        {
            compute += BASE_ZERO;
        }
        temp._number = digitMult(a._number, getDigit(b._number, i), compute);
        result += temp;
    }
    result._sign = a._sign * b._sign;
    if (result._number.empty() || result._number == BASE_ZERO)
    {
        result._number = DEFAULT;
        result._sign = 1;
    }

    return result;
}

/**
 * Perform division on relatively small number
 * @param divided divided
 * @param divisor divisor
 * @return quotient
 */
big_integer smallDivision(const big_integer &divided, const big_integer &divisor)
{
    big_integer i(BASE_ZERO);
    big_integer one(BASE_ONE);
    while (i * divisor <= divided)
    {
        i += one;
    }
    i -= one;
    return i;
}

/**
 * get to power of 2 int as big_integer
 * @param a a
 * @param b b
 * @return a power b
 */
big_integer power(int a, int b)
{
    big_integer result(1);
    for (int i = 0; i < b; i++)
    {
        result *= a;
    }
    return result;
}

/**
 * Division operator
 * @param a divided
 * @param b divisor
 * @return quotient
 */
big_integer operator/(const big_integer &a, const big_integer &b)
{

    big_integer reminder(a), divisor(b),
            quotient(BASE_ZERO), zero(BASE_ZERO), toDivide(BASE_ZERO), result(BASE_ZERO);\

    if (b == zero) // Handling division by zero
    {
        return big_integer(DEFAULT);
    }
    reminder._sign = 1;
    divisor._sign = 1;
    while (reminder >= divisor)
    {
        int i = 1;
        toDivide = reminder;
        auto counter = (int) toDivide._number.length();
        quotient._number = DEFAULT;
        big_integer smallDivided;
        while (quotient == zero)
        {
            smallDivided._number = getDigits(toDivide._number, i);
            quotient = smallDivision(smallDivided, divisor);
            i++;
            counter--;
        }
        big_integer coef = power(BASE, counter); //coefficient
        reminder = smallDivided - quotient * divisor;
        reminder *= coef;
        reminder += toDivide - smallDivided * coef;
        result += quotient * coef;

    }
    result._sign = a._sign * b._sign;
    if (result._number.empty() || result._number == BASE_ZERO)
    {
        result._number = DEFAULT;
        result._sign = 1;
    }

    return result;
}

/**
 * Modulo operator
 * @param a a
 * @param b b
 * @return a modulo b
 */
big_integer operator%(const big_integer &a, const big_integer &b)
{
    if (b == big_integer(BASE_ZERO)) //division by 0
    {
        return big_integer(DEFAULT);
    }
    big_integer result;
    result = a - (a / b) * b; // compute modulo


    if (result._number.empty() || result._number == BASE_ZERO)
    {
        result._number = DEFAULT;
        result._sign = 1;
    }

    return result;
}

/**
 * *= operator
 * @param other other big_integer
 * @return reference to first
 */
big_integer &big_integer::operator*=(const big_integer &other)
{
    (*this) = (*this) * other;
    return *this;
}

/**
 * /= operator
 * @param other other big_integer
 * @return reference to first
 */
big_integer &big_integer::operator/=(const big_integer &other)
{
    (*this) = (*this) / other;
    return *this;
}

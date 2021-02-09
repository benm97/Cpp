/**
 * @file big_integer.h
 * @author  benm
 * @date 4 sept 2018
 * @section DESCRIPTION
 * Handling very big numbers in strings
 */
// ------------------------------ includes ------------------------------
#ifndef EX1_BIG_INTEGER_H
#define EX1_BIG_INTEGER_H

#include <string>
using namespace std;

/**
 * Big integer class
 */
class big_integer
{
public:
    /**
    * Constructor
    */
    big_integer();

    /**
     * Copy constructor
     * @param toCopy
     */
    big_integer(const big_integer &toCopy);

    /**
     * Constructor
     * @param num
     */
    big_integer(int num);

    /**
     * Constructor
     * @param str
     */
    big_integer(string str);

    /**
     * = operator
     * @param toCopy
     * @return
     */
    big_integer &operator=(const big_integer &toCopy);

    /**
     * + operator
     * @param toCopy
     * @return
     */
    friend big_integer operator+(const big_integer &a, const big_integer &b);

    /**
     * - operator
     * @param toCopy
     * @return
     */
    friend big_integer operator-(const big_integer &a, const big_integer &b);

    /**
     * += operator
     * @param toCopy
     * @return
     */
    big_integer &operator+=(const big_integer &other);

    /**
     * -= operator
     * @param toCopy
     * @return
     */
    big_integer &operator-=(const big_integer &other);

    /**
     * *= operator
     * @param toCopy
     * @return
     */
    big_integer &operator*=(const big_integer &other);

    /**
     * /= operator
     * @param toCopy
     * @return
     */
    big_integer &operator/=(const big_integer &other);

    /**
     * * operator
     * @param toCopy
     * @return
     */
    friend big_integer operator*(const big_integer &a, const big_integer &b);

    /**
     * / operator
     * @param toCopy
     * @return
     */
    friend big_integer operator/(const big_integer &a, const big_integer &b);

    /**
     * % operator
     * @param toCopy
     * @return
     */
    friend big_integer operator%(const big_integer &a, const big_integer &b);

    /**
    * Function to get the max in absolute value
    * @param a a
    * @param b b
    * @return max
    */
    friend const big_integer &absMax(const big_integer &a, const big_integer &b);

    /**
     * < Operator
     * @param a
     * @param b
     * @return
     */
    friend bool operator<(const big_integer &a, const big_integer &b);

    /**
     * > Operator
     * @param a
     * @param b
     * @return
     */
    friend bool operator>(const big_integer &a, const big_integer &b);

    /**
     * <= Operator
     * @param a
     * @param b
     * @return
     */
    friend bool operator<=(const big_integer &a, const big_integer &b);

    /**
     * >= Operator
     * @param a
     * @param b
     * @return
     */
    friend bool operator>=(const big_integer &a, const big_integer &b);

    /**
     * == Operator
     * @param a
     * @param b
     * @return
     */
    friend bool operator==(const big_integer &a, const big_integer &b);

    /**
     * != Operator
     * @param a
     * @param b
     * @return
     */
    friend bool operator!=(const big_integer &a, const big_integer &b);

    /**
     * << Operator
     * @param a
     * @param b
     * @return
     */
    friend ostream &operator<<(ostream &os, const big_integer &toPrint);

private:
    string _number;
    int _sign;
};

#endif //EX1_BIG_INTEGER_H
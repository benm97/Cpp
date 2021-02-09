/**
 * @file my_set.h
 * @author  benm
 * @date 4 sept 2018
 * @section DESCRIPTION
 * Handling a set of very big numbers. See the BONUS in class description
 */
// ------------------------------ includes ------------------------------

#ifndef EX1FINAL_MY_SET_H
#define EX1FINAL_MY_SET_H

#include "big_integer.h"


/**
 * A class to handle set of big_integer.
 * BONUS:
 * I used an ordered linked list to print the results in ascending order with the required time
 */
class my_set
{
public:

    /**
     * Ctor
     */
    my_set();

    /**
     * Copy ctor
     * @param other
     */
    my_set(const my_set &other);

    /**
     * Destructor
     */
    ~my_set();

    /**
     * =operator
     * @param other
     * @return
     */
    my_set &operator=(const my_set &other);

    /**
     * Check if a big_integer is in set
     * @param number number to search
     * @return true iff in
     */
    bool is_in_set(const big_integer &number) const;

    /**
     * Add number to the set, keeping it ordered
     * @param number to add
     * @return true if added
     */
    bool add(const big_integer &number);

    /**
     * Remove number from the set, keeping it ordered
     * @param number to delete
     * @return true if removed
     */
    bool remove(const big_integer &number);

    /**
     * Compute the sum of the elements
     * @return sum
     */
    big_integer sum_set();

    /**
     * - Operator for sets
     * @param a
     * @param b
     * @return
     */
    friend my_set operator-(const my_set &a, const my_set &b);

    /**
     * - Operator for sets
     * @param a
     * @param b
     * @return
     */
    friend my_set operator|(const my_set &a, const my_set &b);

    /**
     * | Operator for sets
     * @param a
     * @param b
     * @return
     */
    friend my_set operator&(const my_set &a, const my_set &b);

    /**
     * & Operator for sets
     * @param a
     * @param b
     * @return
     */
    friend ostream &operator<<(ostream &os, const my_set &toPrint);

private:
    /**
     * Node class
     */
    class Node
    {
    public:
        big_integer _data;
        Node *_next;

    };

    Node *_head;
};


#endif //EX1FINAL_MY_SET_H

/**
 * @file my_set.cpp
 * @author  benm
 * @date 4 sept 2018
 * @section DESCRIPTION
 * Handling a set of very big numbers. See the BONUS in class description
 */
// ------------------------------ includes ------------------------------

#include <iostream>
#include "my_set.h"

using namespace std;
// ------------------------------ functions -----------------------------

/**
 * Ctor
 */
my_set::my_set()
{
    _head = nullptr;
}

/**
 * Copy ctor
 * @param other
 */
my_set::my_set(const my_set &other)
{
    _head = nullptr;
    Node *current = other._head;
    while (current)
    {
        add(current->_data);
        current = current->_next;
    }
}

/**
 * Destructor
 */
my_set::~my_set()
{
    Node *current = _head;
    while (current)
    {
        Node *nextNode = current->_next;
        delete current;
        current = nextNode;
    }
}

/**
 * Operator=
 * @param other
 * @return
 */
my_set &my_set::operator=(const my_set &other)
{

    Node *toDelete = _head;
    while (toDelete)
    {
        Node *nextNode = toDelete->_next;
        delete toDelete;
        toDelete = nextNode;
    }
    _head = nullptr;
    Node *current = other._head;
    while (current)
    {
        add(current->_data);
        current = current->_next;
    }
    return *this;
}

/**
 * Check if a big_integer is in set
 * @param number number to search
 * @return true iff in
 */
bool my_set::is_in_set(const big_integer &number) const
{
    Node *current = _head;
    while (current)
    {
        if (current->_data == number)
        {
            return true;
        }
        current = current->_next;
    }
    return false;
}

/**
 * Add number to the set, keeping it ordered
 * @param number to add
 * @return true if added
 */
bool my_set::add(const big_integer &number)
{
    if (_head == nullptr) // If the set empty
    {
        auto *numNode = new Node;
        numNode->_data = number;
        numNode->_next = nullptr;
        _head = numNode;
        return true;
    }
    if (_head->_data > number) // If we need to put it at the start
    {
        auto *numNode = new Node;
        numNode->_data = number;
        numNode->_next = _head;
        _head = numNode;
        return true;
    }
    if (_head->_data == number) // If it's already the head
    {
        return false;
    }
    Node *current = _head, *next = _head->_next;
    while (next)
    {
        if (next->_data == number)
        {
            return false;
        }
        else if (next->_data < number)
        {
            current = current->_next;
            next = next->_next;
        }
        else
        {
            auto *numNode = new Node;
            numNode->_data = number;
            numNode->_next = next;
            current->_next = numNode;
            return true;
        }
    }
    // If we reach the end, putting it at the end
    auto *numNode = new Node;
    numNode->_data = number;
    numNode->_next = nullptr;
    current->_next = numNode;
    return true;
}

/**
 * Remove number from the set, keeping it ordered
 * @param number to delete
 * @return true if removed
 */
bool my_set::remove(const big_integer &number)
{
    if (_head == nullptr) // If the set empty
    {
        return false;
    }
    if (_head->_data == number) // If we need to remove the head
    {
        Node *tmp = _head;
        _head = _head->_next;
        delete tmp;
        return true;
    }
    Node *current = _head;
    while (current->_next)
    {
        if ((current->_next)->_data == number)
        {
            Node *tmp = current->_next;
            current->_next = (current->_next)->_next;
            delete tmp;
            return true;
        }
        current = current->_next;
    }
    return false;
}

/**
 * Compute the sum of the elements
 * @return sum
 */
big_integer my_set::sum_set()
{
    big_integer sum;
    Node *current = _head;
    while (current)
    {
        sum += current->_data;
        current = current->_next;
    }
    return sum;
}

/**
 * Operator- for sets
 * @param a
 * @param b
 * @return
 */
my_set operator-(const my_set &a, const my_set &b)
{
    my_set result;
    result._head = nullptr;
    my_set::Node *current = a._head;
    while (current)
    {
        if (!b.is_in_set(current->_data))
        {
            result.add(current->_data);
        }

        current = current->_next;
    }
    return result;
}

/**
 * Operator| for sets
 * @param a
 * @param b
 * @return
 */
my_set operator|(const my_set &a, const my_set &b)
{
    my_set result;
    result._head = nullptr;
    my_set::Node *current = a._head;
    while (current)
    {
        result.add(current->_data);
        current = current->_next;
    }
    current = b._head;
    while (current)
    {
        result.add(current->_data);
        current = current->_next;
    }
    return result;
}

/**
 * Operator& for sets
 * @param a
 * @param b
 * @return
 */
my_set operator&(const my_set &a, const my_set &b)
{
    my_set result;
    result._head = nullptr;
    my_set::Node *current = a._head;
    while (current)
    {
        if (b.is_in_set(current->_data))
        {
            result.add(current->_data);
        }

        current = current->_next;
    }
    return result;
}

/**
 * Operator<< for sets, print in ascending order
 * @param os stream
 * @param toPrint
 * @return reference to the stream
 */
ostream &operator<<(ostream &os, const my_set &toPrint)
{
    if (toPrint._head == nullptr)
    {
        os << endl;
        return os;
    }
    auto *current = toPrint._head;
    while (current)
    {
        os << current->_data << endl;
        current = current->_next;
    }

    return os;
}

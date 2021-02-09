#ifndef EX3_MY_SET_HPP
#define EX3_MY_SET_HPP

#include "my_set.h"

/**
 *
 * @tparam T
 */
template<class T>
my_set<T>::my_set():_root(nullptr), _size(0)
{}


/**
 *
 * @tparam T
 * @param other
 */
template<class T>
my_set<T>::my_set(const my_set &other)
{
    _size = 0;
    _root = nullptr;
    for (iterator it = other.cbegin(); it != other.cend(); it++)
    {
        insert(*it);
    }
}

/**
 *
 * @tparam T
 * @tparam InputIterator
 * @param first
 * @param last
 */
template<typename T>
template<class InputIterator>
my_set<T>::my_set(InputIterator first, InputIterator last)
{
    _size = 0;
    _root = nullptr;
    for (InputIterator i = first; i != last; i++)
    {
        insert(*i);
    }

}

/**
 *
 * @tparam T
 * @param a
 * @return
 */
template<class T>
std::shared_ptr<Node<T>> Node<T>::maxElement(std::shared_ptr<Node<T>> a)
{
    std::shared_ptr<Node> current = a;
    if (!current)
    {
        return nullptr;
    }
    while (current->_right != nullptr)
    {
        current = current->_right;
    }
    return current;
}

/**
 *
 * @tparam T
 * @param a
 * @return
 */
template<class T>
std::shared_ptr<Node<T>> Node<T>::minElement(std::shared_ptr<Node<T>> a)
{
    std::shared_ptr<Node> current = a;
    if (!current)
    {
        return nullptr;
    }
    while (current->_left != nullptr)
    {
        current = current->_left;
    }
    return current;
}

/**
 *
 * @tparam T
 * @param a
 * @return
 */
template<class T>
std::shared_ptr<Node<T>> my_set<T>::successorHelper(std::shared_ptr<Node<T>> a)
{
    std::shared_ptr<Node<T>> current = a;
    while ((current->_parent)->_right != nullptr &&
           current->_data == ((current->_parent)->_right)->_data)
    {
        current = current->_parent;
    }
    return current->_parent;
}

/**
 *
 * @tparam T
 * @param a
 * @param searchRoot
 * @return
 */
template<class T>
std::shared_ptr<Node<T>>
my_set<T>::successor(std::shared_ptr<Node<T>> a, const std::shared_ptr<Node<T>> searchRoot)
{
    std::shared_ptr<Node<T>> current = a;

    if (current->_right != nullptr)
    {
        return Node<T>::minElement(current->_right);
    }
    else if (current->_data == Node<T>::maxElement(searchRoot)->_data)
    {
        return current;
    }
    else
    {
        return successorHelper(current);
    }

}

template<class T>
BTreeIterator<T> &BTreeIterator<T>::operator=(BTreeIterator<T> iter)
{
    _pointer = iter._pointer;
    _reversed = iter._reversed;
    return *this;
}

/**
 * move operator =
 * @tparam T
 * @param toCopy
 * @return
 */
template<typename T>
my_set<T> &my_set<T>::operator=(my_set &&toCopy) noexcept
{
    if (this != &toCopy)
    {

        iterator iter;
        clear();
        for (iter = toCopy.cbegin(); iter != toCopy.cend(); iter++)
        {
            insert(*iter);
        }
        toCopy._size = 0;
        toCopy._root = nullptr;

    }
    return *this;
}

/**
 *
 * @tparam T
 * @param val
 * @return
 */
template<class T>
typename my_set<T>::const_iterator my_set<T>::find(const T &val) const
{
    std::shared_ptr<Node<T>> value = findHelper(val, _root);
    if (value->_data == val)
    {
        return BTreeIterator<T>(value);
    }
    return BTreeIterator<T>();
}

/**
 *
 * @tparam T
 * @param val
 * @return
 */
template<class T>
typename my_set<T>::iterator my_set<T>::find(const T &val)
{
    std::shared_ptr<Node<T>> value = findHelper(val, _root);
    if (value->_data == val)
    {
        return BTreeIterator<T>(value);
    }
    return BTreeIterator<T>();
}

template<class T>
BTreeIterator<T> &BTreeIterator<T>::operator++()
{
    if (!_reversed)
    {
        std::shared_ptr<Node<T>> curr = _pointer;
        while (curr->_parent != nullptr)
        {
            curr = (curr->_parent);
        }
        T data = _pointer->_data;
        _pointer = my_set<T>::successor(_pointer, curr);
        if (_pointer->_data == data)
        {
            _pointer = nullptr;
        }
    }
    else
    {
        _pointer = my_set<T>::predecessor(_pointer);
    }
    return *this;
}

/**
 *
 * @tparam T
 * @return
 */
template<class T>
const BTreeIterator<T> BTreeIterator<T>::operator++(int)
{
    BTreeIterator<T> oldNode(*this);
    ++(*this);
    return oldNode;
}

template<class T>
BTreeIterator<T> &BTreeIterator<T>::operator--()
{

    if (!_reversed)
    {
        _pointer = my_set<T>::predecessor(_pointer);
    }
    else
    {
        std::shared_ptr<Node<T>> curr = _pointer;
        while (curr->_parent != nullptr)
        {
            curr = (curr->_parent);
        }
        T data = _pointer->_data;
        _pointer = my_set<T>::successor(_pointer, curr);
        if (_pointer->_data == data)
        {
            _pointer = nullptr;
        }
    }
    return *this;

}

/**
 *
 * @tparam T
 * @return
 */
template<class T>
const BTreeIterator<T> BTreeIterator<T>::operator--(int)
{
    BTreeIterator<T> oldNode(*this);
    --(*this);
    return oldNode;
}

/**
 *
 * @tparam T
 * @param val
 * @param searchRoot
 * @return
 */
template<class T>
std::shared_ptr<Node<T>>
my_set<T>::findHelper(const T &val, const std::shared_ptr<Node<T>> searchRoot) const
{

    if (val > searchRoot->_data && searchRoot->_right != nullptr)
    {
        return findHelper(val, searchRoot->_right);
    }
    else if (val < searchRoot->_data && searchRoot->_left != nullptr)
    {
        return findHelper(val, searchRoot->_left);
    }
    else
    {
        return searchRoot;
    }

}

/**
 *
 * @tparam T
 * @param val
 * @param searchRoot
 * @return
 */
template<class T>
std::pair<BTreeIterator<T>, bool>
my_set<T>::insertHelper(const T &val, std::shared_ptr<Node<T>> searchRoot)
{
    std::shared_ptr<Node<T>> newElement = std::make_shared<Node<T>>();
    if (_root == nullptr)
    {
        newElement->_data = val;
        _root = newElement;
        _size++;
        return std::pair<BTreeIterator<T>, bool>(BTreeIterator<T>(searchRoot), true);
    }
    std::shared_ptr<Node<T>> found = findHelper(val, searchRoot);
    if (found->_data == val)
    { // If the value already in
        return std::pair<BTreeIterator<T>, bool>(BTreeIterator<T>(found), false);
    }
    else if (found->_data < val)
    {

        newElement->_data = val;
        newElement->_parent = found;
        found->_right = newElement;
        _size++;
        return std::pair<BTreeIterator<T>, bool>(BTreeIterator<T>(found->_right), true);
    }
    else if (found->_data > val)
    {

        newElement->_data = val;
        newElement->_parent = found;
        found->_left = newElement;
        _size++;
        return std::pair<BTreeIterator<T>, bool>(BTreeIterator<T>(found->_left), true);
    }
    return std::pair<BTreeIterator<T>, bool>(BTreeIterator<T>(), false);
}

/**
 *
 * @tparam T
 * @param val
 * @return
 */
template<class T>
std::pair<BTreeIterator<T>, bool> my_set<T>::insert(const my_set::value_type &val)
{
    return insertHelper(val, _root);
}

/**
 *
 * @tparam T
 * @return
 */
template<class T>
typename my_set<T>::const_iterator my_set<T>::cbegin() const
{
    std::shared_ptr<Node<T>> node = Node<T>::minElement(_root);
    return const_iterator(node);
}

/**
 *
 * @tparam T
 * @return
 */
template<class T>
typename my_set<T>::const_iterator my_set<T>::cend() const
{
    return const_iterator(nullptr);
}

/**
 *
 * @tparam T
 * @return
 */
template<class T>
typename my_set<T>::const_iterator my_set<T>::crbegin() const
{
    std::shared_ptr<Node<T>> node = Node<T>::maxElement(_root);
    return const_iterator(node, true);
}

/**
 *
 * @tparam T
 * @return
 */
template<class T>
typename my_set<T>::const_iterator my_set<T>::crend() const
{
    return const_iterator(nullptr, true);
}

/**
 * erase
 * @tparam T
 * @param position
 */
template<class T>
typename my_set<T>::iterator my_set<T>::erase(my_set::const_iterator position)
{
    std::shared_ptr<Node<T>> mySuccessor = successor(position._pointer, _root);
    std::shared_ptr<Node<T>> toDelete = findHelper(*position, _root);
    if (!toDelete)
    {
        return iterator();
    }
    if (toDelete->_left == nullptr && toDelete->_right == nullptr)
    {
        deleteLeaf(toDelete);
    }
    else if (toDelete->_left != nullptr && toDelete->_right == nullptr)
    {
        deleteWithLeft(toDelete);
    }
    else if (toDelete->_left == nullptr)
    {
        deleteWithRight(toDelete);
    }
    else
    {
        deleteWithTwo(toDelete);

    }
    _size--;
    toDelete->_parent = nullptr;
    return iterator(mySuccessor);
}

/**
 * delete a leaf
 * @tparam T
 * @param found
 */
template<class T>
void my_set<T>::deleteLeaf(std::shared_ptr<Node<T>> &found)
{
    if (found == _root)
    { // If this is the last element
        _root = nullptr;
    }
    else if (found->_parent->_right != nullptr &&
             found->_parent->_right->_data == found->_data)
    {
        found->_parent->_right = nullptr;
    }
    else
    {
        found->_parent->_left = nullptr;
    }
}

/**
 *
 * @tparam T
 * @param found
 */
template<class T>
void my_set<T>::deleteWithLeft(std::shared_ptr<Node<T>> &found)
{
    if (found->_parent != nullptr)
    { //If it's not the root
        if (found->_data < found->_parent->_data)
        {//If we are at the left
            found->_parent->_left = found->_left;
            found->_parent->_left->_parent = found->_parent;
        }
        else
        { //At the right
            found->_parent->_right = found->_left;
            found->_parent->_right->_parent = found->_parent;
        }
    }
    else
    {
        _root = found->_left;
        found->_left->_parent = nullptr;
    }

}

/**
 *
 * @tparam T
 * @param found
 */
template<class T>
void my_set<T>::deleteWithRight(std::shared_ptr<Node<T>> &found)
{
    if (found->_parent != nullptr)
    { //If it's not the root
        if (found->_data < found->_parent->_data)
        { //If we are at the left
            found->_parent->_left = found->_right;
            found->_parent->_left->_parent = found->_parent;
        }
        else
        { // At the right
            found->_parent->_right = found->_right;
            found->_parent->_right->_parent = found->_parent;
        }
    }
    else
    {
        _root = found->_right;
        found->_right->_parent = nullptr;
    }
}

/**
 *
 * @tparam T
 * @param found
 */
template<class T>
void my_set<T>::deleteWithTwo(std::shared_ptr<Node<T>> &found)
{
    auto nextNode = successor(found, _root);
    T nextValue = nextNode->_data;
    erase(iterator(nextNode)); // Delete the successor
    found->_data = nextValue; // Putting the successor at our place
    _size++; //Adding it to the elements number
}

/**
 *
 * @tparam T
 */
template<class T>
void my_set<T>::clear() noexcept
{
    std::shared_ptr<Node<T>> maximal = Node<T>::maxElement(_root);
    while (maximal)
    {
        erase(maximal->_data);
        maximal = Node<T>::maxElement(_root);
    }
    _size = 0;
}

/**
 *
 * @tparam T
 * @param val
 * @return
 */
template<class T>
int my_set<T>::erase(const T &val)
{
    auto found = find(val);
    erase(found);
    if (*found)
    {
        return 1;
    }
    return 0;
}

/**
 *
 * @tparam T
 * @param a
 * @return
 */
template<class T>
std::shared_ptr<Node<T>> my_set<T>::predecessor(std::shared_ptr<Node<T>> a)
{
    std::shared_ptr<Node<T>> predecessor;
    if (a->_left)
    {

        a = a->_left;
        predecessor = Node<T>::maxElement(a);
        if (predecessor && predecessor->_data > a->_parent->_data)
        {
            return nullptr;
        }
        return predecessor;
    }
    else if (a->_right)
    {
        std::shared_ptr<Node<T>> tmp = a;
        a = a->_parent;
        while (a && tmp == a->_left)
        {
            a = a->_parent;
        }
        predecessor = a;
        if (predecessor && predecessor->_data > tmp->_data)
        {
            return nullptr;
        }
        return predecessor;
    }
    else
    {
        predecessor = a->_parent;
        if (predecessor->_data > a->_data)
        {
            return nullptr;
        }
        return predecessor;
    }
}

/**
 *
 * @tparam T
 * @param x
 */
template<class T>
void my_set<T>::swap(my_set<T> &other)
{
    my_set<T> tmp = *this;
    *this = other;
    other = tmp;
}


/**
 *
 * @tparam T
 * @param position
 * @param val
 * @return
 */
template<class T>
typename my_set<T>::iterator
my_set<T>::insert(my_set::const_iterator position, const my_set<T>::value_type &val)
{
    auto mySuccessor = successor(position._pointer);
    if (val > position._pointer->_data && (!mySuccessor || val < mySuccessor->_data))
    {
        return insertHelper(val, position._pointer).first;
    }
    else
    {
        return insertHelper(val, _root).first;
    }
}

/**
 * insert that receives a rvalue to insert
 * @tparam T
 * @param val
 * @return
 */
template<typename T>
std::pair<typename my_set<T>::iterator, bool> my_set<T>::insert(my_set::value_type &&val)
{
    return insertHelper(val, _root);
}

/**
 * insert that receives a position and a val
 * @tparam T
 * @param position
 * @param val
 * @return
 */
template<typename T>
typename my_set<T>::iterator my_set<T>::insert(my_set::const_iterator position, value_type &&val)
{
    return insert(position, val);
}

/**
 * move copy constructor
 * @tparam T
 * @param toCopy
 */
template<typename T>
my_set<T>::my_set(my_set &&toCopy) noexcept
{
    _size = 0;
    _root = nullptr;
    iterator iter;
    for (iter = toCopy.cbegin(); iter != toCopy.cend(); iter++)
    {
        insert(*iter);
    }
    toCopy._root = nullptr;
    toCopy._size = 0;
}

/**
 *
 * @tparam T
 * @tparam InputIterator
 * @param first
 * @param last
 */
template<class T>
template<class InputIterator>
void my_set<T>::insert(InputIterator first, InputIterator last)
{

    auto iter = first;
    std::shared_ptr<Node<T>> myNode;
    for (iter; iter != last; ++iter)
    {
        myNode = findHelper(*iter, _root);
        if (!myNode)
        {
            insert(*iter);
        }
    }
}

/**
 *
 * @tparam T
 * @param first
 * @param last
 */
template<class T>
typename my_set<T>::iterator my_set<T>::erase(my_set::iterator first, my_set::iterator last)
{
    iterator iter = last;
    T tmp;
    while (iter != first)
    {
        tmp = *iter;
        iter--;
        erase(tmp);
    }
    return iter;
}

/**
 *
 * @tparam T
 * @param toCopy
 * @return
 */
template<class T>
my_set<T> &my_set<T>::operator=(const my_set &toCopy)
{
    if (!toCopy._root)
    {
        _root = nullptr;
        _size = 0;
        return *this;
    }
    if (&toCopy == this)
    {
        return *this;
    }
    clear();

    for (auto iter = toCopy.cbegin(); iter != toCopy.cend(); ++iter)
    {
        insert(*iter);
    }
    return *this;
}

#endif
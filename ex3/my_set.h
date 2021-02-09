//
// Created by benm on 10/16/18.
//

#ifndef EX3_MY_SET_H
#define EX3_MY_SET_H

#include <memory>
#include <unordered_map>

template<typename T>
class BTreeIterator;

template<typename T>
class Node;

template<typename T>
class my_set;

template<class T>
/**
 *
 * @tparam T
 */
class Node
{
public:
    /**
     * Ctor
     */
    Node()= default;

    T _data;
    std::shared_ptr<Node<T>> _left;
    std::shared_ptr<Node<T>> _right;
    std::shared_ptr<Node<T>> _parent;

    /**
    * destructor
    */
    ~Node() = default;
    /**
     * get max element
     * @param a
     * @return
     */
    static std::shared_ptr<Node<T>> maxElement(std::shared_ptr<Node<T>> a);

    /**
     * get min element
     * @param a
     * @return
     */
    static std::shared_ptr<Node<T>> minElement(std::shared_ptr<Node<T>> a);

};

/**
 *
 * @tparam T
 */
template<class T>
class BTreeIterator
{
public:
    /**
     * Ctor
     */
    BTreeIterator<T>() : _pointer(nullptr), _reversed(false)
    {}

    /**
     *
     * @param myNode
     * @param reversed
     */
    explicit BTreeIterator<T>(std::shared_ptr<Node<T>> myNode, bool reversed = false) : _pointer(myNode),
                                                                                   _reversed(
                                                                                           reversed)
    {}

    BTreeIterator& operator=(BTreeIterator<T> iter);
    /**
     *
     * @return
     */
    T &operator*() const
    { return _pointer->_data; }

    /**
     *
     * @return
     */
    std::shared_ptr<T> operator->() const
    { return std::make_shared<T>(_pointer->_data); }

    /**
     *
     * @return
     */
    BTreeIterator<T> &operator++();

    /**
     *
     * @return
     */
    const BTreeIterator<T> operator++(int);

    /**
     *
     * @return
     */
    BTreeIterator<T> &operator--();

    /**
     *
     * @return
     */
    const BTreeIterator<T> operator--(int);

    /**
     *
     * @param rhs
     * @return
     */
    bool operator==(BTreeIterator<T> const &rhs) const
    { return _pointer == rhs._pointer; }

    /**
     *
     * @param rhs
     * @return
     */
    bool operator!=(BTreeIterator<T> const &rhs) const
    { return _pointer != rhs._pointer; }

    /**
     *
     * @return
     */
    BTreeIterator<T> begin()
    {
        std::shared_ptr<Node<T>> curr = _pointer;
        while (curr->_parent != nullptr)
        {
            curr = curr->_parent;
        }
        if (!_reversed)
        {
            return BTreeIterator(Node<T>::minElement(curr), false);
        }
        else
        {
            return BTreeIterator(Node<T>::maxElement(curr), true);
        }
    }

    /**
     *
     * @return
     */
    BTreeIterator<T> end()
    { return BTreeIterator<T>(nullptr); }

    std::shared_ptr<Node<T>> _pointer;
    bool _reversed;

};

/**
 *
 * @tparam T
 */
template<class T>
class my_set
{
public:
    typedef BTreeIterator<T> iterator;
    typedef const BTreeIterator<T> const_iterator;
    typedef T value_type;

    /**
     *
     */
    my_set();

    /**
     *
     * @param other
     */
    my_set(const my_set &other);

    /**
     *
     * @param toCopy
     * @return
     */
    my_set &operator=(const my_set &toCopy);

    /**
    * move operator =
    * @tparam T
    * @param toCopy
    * @return
    */
    my_set& operator=(my_set && toCopy) noexcept;

    /**
     *
     */
    ~my_set(){
        clear();
    }

    /**
    * move copy constructor
    * @tparam T
    * @param toCopy
    */
    my_set(my_set && toCopy) noexcept;

    /**
     *
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    my_set(InputIterator first, InputIterator last);

    /**
     *
     * @param a
     * @param searchRoot
     * @return
     */
    static std::shared_ptr<Node<T>>
    successor(std::shared_ptr<Node<T>> a, std::shared_ptr<Node<T>> searchRoot);

    /**
     *
     * @param a
     * @return
     */
    static std::shared_ptr<Node<T>> predecessor(std::shared_ptr<Node<T>> a);

    /**
    * find that receives val
    * @tparam T
    * @param val
    * @return
    */
    const_iterator find (const value_type& val) const;

    /**
    * find that receives val
    * @tparam T
    * @param val
    * @return
    */
    iterator find (const value_type& val);

    /**
     *
     * @param val
     * @return
     */
    std::pair<iterator, bool> insert(const value_type &val);

    /**
    * insert that receives a rvalue to insert
    * @tparam T
    * @param val
    * @return
    */
    std::pair<iterator, bool> insert (value_type && val);
    /**
     *
     * @param position
     * @param val
     * @return
     */
    iterator insert(iterator position, const value_type &val);

    /**
    * insert that receives a position and a val
    * @tparam T
    * @param position
    * @param val
    * @return
    */
    iterator insert (const_iterator position, value_type && val);
    /**
     *
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);

    /**
     *
     * @param position
     */
    iterator erase(const_iterator position);

    /**
     *
     * @param val
     * @return
     */
    int erase(const value_type &val);

    /**
     *
     * @param first
     * @param last
     */
    iterator erase(const_iterator first, const_iterator last);

    /**
     *
     */
    void clear() noexcept;

    /**
     *
     * @return
     */
    unsigned int size() const
    { return _size; }

    /**
     *
     * @return
     */
    bool empty() const
    { return _size == 0; }

    /**
     *
     * @return
     */
    const_iterator cbegin() const;

    /**
     *
     * @return
     */
    const_iterator cend() const;

    /**
     *
     * @return
     */
    const_iterator crbegin() const;

    /**
     *
     * @return
     */
    const_iterator crend() const ;

    /**
     *
     * @param x
     */
    void swap(my_set<T> &);

private:
    /**
     *
     * @param val
     * @param searchRoot
     * @return
     */
    std::pair<BTreeIterator<T>, bool> insertHelper(const T &val, std::shared_ptr<Node<T>> searchRoot);

    /**
     *
     * @param a
     * @return
     */
    static std::shared_ptr<Node<T>> successorHelper(std::shared_ptr<Node<T>> a);

    /**
     *
     * @param found
     */
    void deleteLeaf(std::shared_ptr<Node<T>> &found);

    /**
     *
     * @param found
     */
    void deleteWithLeft(std::shared_ptr<Node<T>> &found);

    /**
     *
     * @param found
     */
    void deleteWithRight(std::shared_ptr<Node<T>> &found);

    /**
     *
     * @param found
     */
    void deleteWithTwo(std::shared_ptr<Node<T>> &found);

    /**
     *
     * @param val
     * @param searchRoot
     * @return
     */
    std::shared_ptr<Node<T>> findHelper(const T &val, std::shared_ptr<Node<T>> searchRoot) const;

    /**
     *
     */
    std::shared_ptr<Node<T>> _root;
    unsigned int _size;
};

#include "my_set.hpp"
#endif //EX3_MY_SET_H

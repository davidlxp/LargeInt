/***************************************************************/
/* Programmer: Xinpeng Liu                                     */
/* Date: February 22, 2022                                     */
/* Purpose:  An iterator class for doubly linked list         */
/***************************************************************/

#ifndef LARGEINT_DLISTITERATOR_H
#define LARGEINT_DLISTITERATOR_H

#include <iostream>
#include <cassert>
using namespace std;
#include "node.h"

template <class T>
class DListIterator {
private:
    node<T>* current;
public:

    /**
     * @Brief default constructor which initialize the iterator
     * but not letting the iterator points to anything, basically
     * the current pointer will be set equals to "nullptr"
     */
    DListIterator();

    /**
     * @Brief constructor which initialize the iterator by
     * telling it to point to a certain node
     * @Detail usually it will be used as "DListIterator(first)"
     * or "DListIterator(last)" to make the iterator points to
     * the begin or end node of the LinkedList
     * @Input an pointer to the node which the user want the
     * iterator points to
     */
    DListIterator(node<T>* ptr);

    /**
     * @Brief the destructor, we will set pointer "current"
     * to nullptr in it
     */
    ~DListIterator();

    /**
     * @Brief check if the "current" pointer of iterator points
     * to NULL or a node
     * @Detail it will be useful when the client tries to iterate
     * an LinkedList. For example, the client can do:
     *
     *      while(!iterator.isNull())
     *      {
     *          T info = *iterator;
     *          (...using info to do something...)
     *          iterator++;
     *      }
     * @Output if the "current" pointer of iterator is pointing to
     * "nullptr", it will return TRUE. Otherwise, return FALSE
     */
    bool isNull();

    /**
     * @Brief check whether the node, which Iterator
     * points to, has a next node or not
     * @Output if the iterator is currently on a node, and it has next node,
     * the function return TRUE. Otherwise, if the iterator is currently on nullptr,
     * or the node which iterator currently at doesn't have next node, function
     * returns FALSE.
     */
    bool hasNext();

    /**
     * @Brief check whether the node, which Iterator
     * points to, has a previous node or not
     * @Output if the iterator is currently on a node, and it has previous node,
     * the function return TRUE. Otherwise, if the iterator is currently on nullptr,
     * or the node which iterator currently at doesn't have previous node, function
     * returns FALSE.
     */
    bool hasPrev();

    /**
     * @Brief let "current" ptr advances to the next location. It
     * could move to a "next node" or move to "nullptr".
     * @Warning used "assert" to terminate the program if trying to move
     * to next when the "current" pointer = nullptr
     * @Detail returning an Iterator by reference, so user can do
     * cascade "next()" like "x.next().next()"
     */
    DListIterator<T>& next();

    /**
     * @Brief let "current" ptr moves back to the previous location. It
     * could move to a "previous node" or move to "nullptr".
     * @Warning used "assert" to terminate the program if trying to move
     * to previous when the "current" pointer = nullptr
     */
    DListIterator<T>& prev();

    /**
     * @Brief return "info" from node which this iterator currently at
     * @Warning used "assert" to terminate the program if trying to
     * getItem when the"current" pointer = nullptr
     */
    T getItem();

    /**
     * @Brief print "info" from node which this iterator currently at
     * @Warning used "assert" to terminate the program if trying to
     * printItem when the "current" pointer = nullptr
     */
    void printItem();

    /**
     * @Brief overloaded operator* to get "info" from node which
     * this iterator currently at
     * @Detail "return getItem()" in the function
     */
    T operator*();

    /**
     * @Brief overloaded "++" to enable "current" ptr advances to the next node
     * Prefix version --> "++x"
     */
    DListIterator<T>& operator++();

    /**
     * @Brief overloaded "++" to enable "current" ptr advances to the next node.
     * Postfix version --> "x++"
     */
    DListIterator<T>& operator++(int);

    /**
     * @Brief overloaded "--" to enable "current" ptr go back to the previous node.
     * Prefix version --> "--x"
     */
    DListIterator<T> operator--();

    /**
     * @Brief overloaded "--" to enable "current" ptr go back to the previous node.
     * Prefix version --> "x--"
     */
    DListIterator<T>& operator--(int);

    /**
     * @Brief overloaded "==" and "!=" to check if two Iterator point to the same node
     */
    const bool operator==(const DListIterator<T>& other);
    const bool operator!=(const DListIterator<T>& other);

};

#endif //LARGEINT_DLISTITERATOR_H

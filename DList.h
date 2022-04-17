/***************************************************************/
/* Programmer: Xinpeng Liu                                     */
/* Date: February 22, 2022                                     */
/* Purpose: an unsorted doubly linked list class               */
/***************************************************************/

#ifndef LARGEINT_DLIST_H
#define LARGEINT_DLIST_H

#include <iostream>
#include "node.h"
#include "DListIterator.cpp"
using namespace std;

template <class T>
class DList{
private:
    node<T>* first;     // a pointer points to the 1st node of the list
    node<T>* last;      // a pointer points to the last node of the list
    int length;         // indicates how many items are there in the list

    /**
     * @Brief destroy all the nodes in a doubly linkedList
     * and set the "first" and "last" pointer to nullptr,
     * also set the "length" variable to 0
     */
    void destroy();

    /**
     * @Brief make a copy of an list
     * @Input the reference of another LinkedList object which you
     * want to copy information from
     * @Detail copying info from another LinkedList to the current
     * LinkedList node-by-node.
     * @Requirment The current LinkedList has to be
     * empty to use this copy() function
     */
    void copy(const DList<T>& other);

public:
    DList();                                           // Constructor
    ~DList();                                          // Destructor
    DList(const DList<T>& other);                      // Copy Constructor

    /**
     * @Brief overloading the operator=
     * @Detail it enables copying the value from another list to
     * overwrite the current list who calls this function. This function
     * will firstly destroy() the current list, then implement copy().
     * @Input a reference of another instantiated LinkedList object, and
     * const means this object can't be modified within this function
     * @Output a reference of the current LinkedList object. This return
     * value will enable cascade equal between multiple LinkedList objects
     */
    DList<T>& operator=(const DList<T>& other);

    /**
     * @Brief check whether the list is empty
     * @Detail the function will check if pointer "first"
     * equals to nullptr
     * @Output if the LinkedList is empty, the function will
     * give TRUE. Otherwise, it will give FALSE
     */
    bool isEmpty() const;

    /**
     * @Brief delete one item from the list.
     * @Detail If an item has multiple appearances in the list,
     * only delete the first one.
     * @Input an value which user want to delete will be
     * passed into the function as parameter
     */
    void deleteItem(T);

    /**
     * @Brief check whether an item is in the list
     * @Input an item which user want to search for will be
     * passed into the function as parameter
     * @Output If the item found in the List, the function
     * will return TRUE. Otherwise, it returns FALSE
     */
    bool searchItem(T) const;

    /**
     * @Brief get how many items in a list
     * @Output return the value of member variable "length"
     */
    int getLength() const;

    /**
     * @Brief insert to the front of the double linkedList
     * @Input an value which user want to insert into the list
     */
    void insertFront(T);

    /**
     * @Brief insert to the back of the double linkedList
     * @Input an value which user want to insert into the list
     */
    void insertBack(T);

    /**
     * @Brief print a doubly linkedList from front to back
     */
    void printList() const;

    /**
     * @Brief return an Iterator points to the 1st node of the list
     */
    DListIterator<T> begin();

    /**
     * @Brief return an Iterator points to the last node of the list
     */
    DListIterator<T> end();
};

#endif //LARGEINT_DLIST_H

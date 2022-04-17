/****************************************************************************/
/* Programmer: Xinpeng Liu                                                  */
/* Date: February 22, 2022                                                  */
/* Purpose:  implementation of an unsorted doubly linked list class         */
/****************************************************************************/

#include "DList.h"

template <class T>
DList<T>::DList()
{
    first = nullptr;
    last = nullptr;
    length = 0;
}

template <class T>
DList<T>::~DList()
{
    destroy();
}

template <class T>
DList<T>::DList(const DList<T>& other)
{
    copy(other);
}

template <class T>
DList<T>& DList<T>::operator=(const DList<T>& other)
{

    /**
     * @Brief passing by reference, means "other" is an object.
     * so we need to use "&other" to get its address
     */
    if (this != &other)                              // avoid self-copy
    {
        destroy();
        copy(other);
    }

    /**
     * @Brief return type of the function is "reference".
     * so we return an object, instead of the pointer
     */
    return *this;
}

template <class T>
bool DList<T>::isEmpty() const
{
    return first == nullptr;
}

template <class T>
void DList<T>::destroy()
{
    /**
     * @CasesToConsider
     * 1. empty list
     * 2. only 1 node
     * 3. normal walk and destroy
     * */

    node<T>* p = nullptr;
    while (first != nullptr)                       // we use "first" pointer to walk, so while "first != nullptr"
    {
        p = first;                                 // we use "p" pointer to delete node
        first = first->next;                       // ptr "first" moves to the next node
        p->next = nullptr;                         // remove the access from prev node to current node
        delete p;                                  // free the memory of prev node

        if (first != nullptr)                      // if "first" is NOT NULL, there were more than 1 node in the list
            first->prev = nullptr;                 // remove the access from current node to prev node
        else                                       // if "first" is NULL, p pointed to the only node in the list
            last = nullptr;                        // after removing the only node, set "last" to NULL
    }
    length = 0;
    p = nullptr;

}

template <class T>
void DList<T>::printList() const
{
    if (isEmpty())
        cout << "" << endl;
    else
    {
        node<T>* p = first;
        while (p != nullptr)
        {
            cout << p->info << " ";
            p = p->next;
        }
        cout << endl;
    }
}

template <class T>
bool DList<T>::searchItem(T item) const
{
    bool res = false;                               // by default return false

    if (isEmpty())
        cout << "\nList is empty.\n" << endl;
    else
    {
        node<T>* p = first;
        while (p != nullptr)                        // unsorted list -> thus, no "p->info <= item" needed
        {
            if (p->info == item)
            {
                res = true;
                break;
            }
            p = p->next;
        }
    }

    return res;
}

template <class T>
int DList<T>::getLength() const
{
    return length;
}

template <class T>
void DList<T>::copy(const DList<T>& other)
{
    /**
     * @CasesToConsider
     * 1. "other" is empty
     * 2. "other" has nodes
     * */

    length = other.length;                          // copy the length

    if (other.first == nullptr)                     // if the "other" list is empty
    {
        first = last = nullptr;
    }
    else                                            // when the "other" list is not empty
    {
        first = new node<T>;                        // the following 4 lines copy the first node from other
        first->prev = nullptr;
        first->next = nullptr;
        first->info = other.first->info;

        last = first;                               // let last node equals to first

        node<T> *p = other.first->next;             // let "p" points to 1st node of "other"
        while (p != nullptr)                        // when pointer "p" still points to a node of "other" list
        {
            last->next = new node<T>;               // create the next node

            last->next->info = p->info;             // copy "info" to the next node
            last->next->prev = last;                // build access from "next node" to "current node"
            last->next->next = nullptr;             // set "next" ptr of the "next node" to be null

            last = last->next;                      // move the ptr "last" to the next node
            p = p->next;                            // move the ptr "p" to the next node
        }
        p = nullptr;                                // set "p" ptr to null
    }
}

template <class T>
void DList<T>::insertFront(T item)
{
    /**
     * @CasesToConsider
     * 1. list is empty
     * 2. 1 item in the list
     * 3. multiple items in the list
     * */

    node<T>* p = first;

    first = new node<T>;                            // pointer "first" generates a new node
    first->prev = nullptr;
    first->next = p;
    first->info = item;

    if (p == nullptr)                               // when list was originally empty
        last = first;
    else                                            // when list originally has at least 1 node
        p->prev = first;

    p = nullptr;
    length++;
}

template <class T>
void DList<T>::insertBack(T item)
{
    node<T>* p = last;

    last = new node<T>;                             // pointer "last" generates a new node
    last->prev = p;
    last->next = nullptr;
    last->info = item;

    if (p == nullptr)                               // when list was originally empty
        first = last;
    else                                            // when list originally has at least 1 node
        p->next = last;

    p = nullptr;
    length++;
}

template <class T>
void DList<T>::deleteItem(T item)
{
    /**
     * @CasesToConsider
     * 1. list is empty
     * 2. deleting the only node in the list
     * 3. delete the first node
     * 4. delete the last node
     * 5. delete middle
     * 6. didn't find the item
     * */

    if (isEmpty())                                  // 1. list is empty
        cout << "The list is empty.\n" << endl;
    else
    {
        node<T>* p = nullptr;                       // "p" ptr is for walking and deleting

        if (first->next == nullptr)                 // when there's only 1 node in the list
        {
            if (first->info != item)
                cout << "Item not found.\n" << endl;
            else                                    // 2. deleting the only node
            {
                delete first;
                length--;

                first = nullptr;
                last = nullptr;
            }
        }
        else                                        // when list contains multiple nodes
        {
            if (first->info == item)                // 3. deleting the 1st node
            {
                p = first;
                first = first->next;
                first->prev = nullptr;
                p->next = nullptr;
                delete p;
                length--;

                p = nullptr;
            }
            else if (last->info == item)            // 4. deleting the last node
            {
                p = last;
                last = last->prev;
                last->next = nullptr;
                p->prev = nullptr;
                delete p;
                length--;

                p = nullptr;
            }
            else                                    // 5. walk to find the node to delete
            {
                p = first->next;
                while (p != last && p->info != item)
                {
                    p = p->next;
                }
                if (p->info == item)
                {
                    p->prev->next = p->next;
                    p->next->prev = p->prev;

                    p->next = nullptr;
                    p->prev = nullptr;

                    delete p;
                    length--;

                    p = nullptr;
                }
                else
                    cout << "Item not found.\n" << endl;
            }
        }
    }
}

template <class T>
DListIterator<T> DList<T>::begin() const
{
    DListIterator<T> iterator(first);
    return iterator;
}

template <class T>
DListIterator<T> DList<T>::end() const
{
    DListIterator<T> iterator(last);
    return iterator;
}
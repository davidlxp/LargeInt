/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: February 22, 2022                                           */
/* Purpose:  Implementation of iterator class for doubly linked list */
/*********************************************************************/

#include "DListIterator.h"

template <class T>
DListIterator<T>::DListIterator()
{
    current = nullptr;
}

template <class T>
DListIterator<T>::DListIterator(node<T>* ptr)
{
    current = ptr;
}

template <class T>
DListIterator<T>::~DListIterator<T>()
{
    current = nullptr;
}

template<class T>
bool DListIterator<T>::isNull()
{
    return (current == nullptr);
}

template <class T>
bool DListIterator<T>::hasNext()
{
    bool res = true;
    if (isNull() || current->next == nullptr)
        res = false;
    return res;
}

template <class T>
bool DListIterator<T>::hasPrev()
{
    bool res = true;
    if (isNull() || current->prev == nullptr)
        res = false;
    return res;
}

template <class T>
DListIterator<T>& DListIterator<T>::next()
{
    // pre-validate if the "current" pointer is nullptr or not
    assert (!isNull());
    current = current->next;
    return *this;
}

template <class T>
DListIterator<T>& DListIterator<T>::prev()
{
    // pre-validate if the "current" pointer is nullptr or not
    assert (!isNull());
    current = current->prev;
    return *this;
}

template <class T>
T DListIterator<T>::getItem()
{
    // pre-validate if the "current" pointer is nullptr or not
    assert (!isNull());
    return current->info;
}

template <class T>
void DListIterator<T>::printItem()
{
    // pre-validate if the "current" pointer is nullptr or not
    assert (!isNull());
    cout << "Item: " << getItem() << endl;
}

template <class T>
T DListIterator<T>::operator*()
{
    return getItem();
}

template <class T>
DListIterator<T>& DListIterator<T>::operator++()
{
    return next();
}

template <class T>
DListIterator<T>& DListIterator<T>::operator++(int)
{
    DListIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template <class T>
DListIterator<T> DListIterator<T>::operator--()
{
    return prev();
}

template <class T>
DListIterator<T>& DListIterator<T>::operator--(int)
{
    DListIterator<T> temp = *this;
    --(*this);
    return temp;
}

template <class T>
const bool DListIterator<T>::operator==(const DListIterator<T>& other)
{
    return current == other.current;
}

template <class T>
const bool DListIterator<T>::operator!=(const DListIterator<T>& other)
{
    return !(*this == other);
}

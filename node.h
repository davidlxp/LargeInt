/***************************************************************/
/* Programmer: Xinpeng Liu                                     */
/* Date: February 22, 2022                                     */
/* Purpose: node struct for LinkedList                         */
/***************************************************************/

#ifndef LARGEINT_NODE_H
#define LARGEINT_NODE_H


template <class T>
struct node {
    T info;
    node<T>* next;
    node<T>* prev;
};

#endif //LARGEINT_NODE_H

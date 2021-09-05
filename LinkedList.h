#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class Key,class Info>
class LinkedList{

    struct node{
        Key key;
        Info info;
        node *next;
    };

    node* head;
    node* tail;
    int Size;

    void deleteNode(node* ToDelete);

public:

    LinkedList();
    ~LinkedList();
    node* insert(Key key,Info info);
    void remove(Key key);
    int GetSize();
    Info& Find(Key key);
    void clear();

    class FailureException{};
    class KeyNotFound: public FailureException{};

};

#include "LinkedListImp.h"

#endif //LINKEDLIST_H

//
// Created by Ahmad Ghanayem on 05/09/2021.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

template<class Key,class Info>
class Dict{

    struct node{
        Key Key;
        Info Info;
        Node *next;
    };

    node* head;
    node* tail;
    int Size;

public:

    Dict();
    node* insert(Key key,Info info);
    void remove(Key key);
    int GetSize();
    int GetHeight();
    Info Find(Key key);

};

#endif //UNTITLED_LINKEDLIST_H

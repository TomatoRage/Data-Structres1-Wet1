#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "library1.h"

template<class Key,class Info>
class Dict{

    struct node{

        Key key;
        Info info;
        node* right_son;
        node* left_son;
        node* father;
        int Height;

        node():right_son(nullptr),left_son(nullptr),Height(0),key(new Key),info(new Info) { }
    };

    node* root;
    int Size;

    int height(node* Node);
    int max(int x,int y);

    node* InsertNode(Key key,Info info, node* NodeToAdd);
    node* RemoveNode(Key key,node* NodeToRemove);
    node* RotateRight(node* &Node);
    node* RotateLeft(node* &Node);
    node* FindSmallestNode(node* Tree);
    Info& FindNode(Key key,node* Tree);

public:

    Dict();
    node* insert(Key key,Info info);
    void remove(Key key);
    int GetSize();
    int GetHeight();
    Info Find(Key key);

    class FailureException{};
    class KeyNotFound: public FailureException{};
};

#endif

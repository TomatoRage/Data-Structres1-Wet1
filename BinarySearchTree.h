#ifndef UNTITLED_BINARYSEARCHTREE_H
#define UNTITLED_BINARYSEARCHTREE_H

template<class Key,class Info>
class BST{

    struct node{

        Key key;
        Info info;
        node* right_son;
        node* left_son;
        node* father;
        int Height;

    };

    node* root;
    node* iterator;
    node* PrevIteration;
    int Size;

    int height(node* Node);
    int max(int x,int y);

    node*& InsertNode(Key key,Info& info, node*& NodeToAdd);
    node* RemoveNode(Key key,node* Tree);
    node* RotateRight(node* &Node);
    node* RotateLeft(node* &Node);
    node* FindSmallestNode(node* Tree);
    Info& FindNode(Key key,node* Tree);
    void DeleteNode(node* ToDelete);

public:

    BST();
    ~BST();
    node* insert(Key key,Info& info);
    void remove(Key key);
    int GetSize();
    void ResetIterator();
    Info& NextIteration(Key** key);
    int GetHeight();
    Info& Find(Key key);
    void clear();

    class FailureException{};
    class KeyNotFound: public FailureException{};
};

#include "BinarySearchTreeImp.h"

#endif

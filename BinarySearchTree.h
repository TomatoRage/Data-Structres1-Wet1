#ifndef UNTITLED_BINARYSEARCHTREE_H
#define UNTITLED_BINARYSEARCHTREE_H

template<class Key,class Info>
class BST{

    struct node{

        Key key;
        Info info;
        node* right_son;
        node* left_son;
        int Height;

    };

    node* root;
    int Size;

    int height(node* Node);
    int max(int x,int y);

    node* InsertNode(Key key,Info info, node*& NodeToAdd);
    node* RemoveNode(Key key,node*& NodeToRemove);
    node* RotateRight(node* &Node);
    node* RotateLeft(node* &Node);
    node* FindSmallestNode(node* Tree);
    Info& FindNode(Key key,node* Tree);
    void DeleteNode(node* ToDelete);

public:

    BST();
    ~BST();
    node* insert(Key key,Info info);
    void remove(Key key);
    int GetSize();
    int GetHeight();
    Info& Find(Key key);
    void clear();

    class FailureException{};
    class KeyNotFound: public FailureException{};
};

#include "BinarySearchTreeImp.h"

#endif

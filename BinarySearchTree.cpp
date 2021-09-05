#include "BinarySearchTree.h"

template<class Key,class Info>
BST<Key,Info>::BST(){
    root = nullptr;
    Size = 0;
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key, Info>::insert(Key key, Info info){
    return InsertNode(key,info,root);
}

template<class Key,class Info>
void BST<Key,Info>::remove(Key key) {
    RemoveNode(key,root);
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key, Info>::InsertNode(Key key, Info info, node* NodeToAdd) {

    if(NodeToAdd == nullptr)
    {
        NodeToAdd = new node;
        NodeToAdd->key = key;
        NodeToAdd->info = info;
        NodeToAdd->height = 0;
        NodeToAdd->left_son = NodeToAdd->right_son = nullptr;
        Size++;
    }

    else if(key < NodeToAdd->key){

        NodeToAdd->left_son = insert(NodeToAdd, NodeToAdd->left_son);
        if(height(NodeToAdd->left_son) - height(NodeToAdd->right_son) == 2)
        {
            if(key < NodeToAdd->left_son->key)
                NodeToAdd = RightRotate(NodeToAdd);
            else{
                NodeToAdd->left_son = RotateLeft(NodeToAdd->left_son);
                NodeToAdd = RotateRight(NodeToAdd);
            }

        }

        else if(key > NodeToAdd->key)
        {
            NodeToAdd->right_son = insert(key, NodeToAdd->right_son);
            if(height(NodeToAdd->left_son) - height(NodeToAdd->right_son) == -2)
            {
                if(key > NodeToAdd->right_son->key)
                    NodeToAdd = RotateLeft(NodeToAdd);
                else{
                    NodeToAdd->right_son = RotateRight(NodeToAdd->right_son);
                    NodeToAdd = RotateLeft(NodeToAdd);
                }
            }

        }

        NodeToAdd->height = max(height(NodeToAdd->left_son), height(NodeToAdd->right_son))+1;
        return NodeToAdd;
    }

}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::RotateRight(node *&Node) {

    node* TempNode = Node->left_son;
    Node->left_son = TempNode->right_son;
    TempNode->right_son = Node;
    Node->Height = max(height(Node->left_son), height(Node->right_son))+1;
    TempNode->Height = max(height(TempNode->left_son), Node->Height)+1;
    return TempNode;

}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::RotateLeft(node *&Node){

    node* TempNode = Node->right_son;
    Node->right = TempNode->left_son;
    TempNode->left_son = Node;
    Node->Height = max(height(Node->left_son), height(Node->right_son))+1;
    TempNode->Height = max(height(TempNode->right_son), Node->Height)+1 ;
    return TempNode;
}

template<class Key,class Info>
int BST<Key,Info>::height(node *Node) {
    int Right,Left = 0;
    if(Node == nullptr)
        return 0;
    if(Node->right_son)
       Right = Node->right_son->Height;
    if(Node->left_son)
        Left = Node->left_son->Height;
    return max(Right,Left)+1;
}

template<class Key,class Info>
int BST<Key,Info>::max(int x, int y) {
    return (x > y ? x : y);
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::FindSmallestNode(node *Tree) {
    if(Tree == nullptr)
        return nullptr;
    else if(Tree->left_son == nullptr)
        return Tree;
    else
        FindSmallestNode(Tree);
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::RemoveNode(Key key, node *Tree) {

    if(Tree == nullptr)
        throw KeyNotFound();

    else if(key < Tree->key)
        Tree->left_son = remove(key, Tree->left_son);
    else if(key > Tree->key)
        Tree->right_son = remove(key, Tree->right_son);

    else if(Tree->left_son && Tree->right_son)
    {
        node* temp,ToReplace = FindSmallestNode(Tree->right);
        ToReplace->left_son = Tree->left_son;
        temp = ToReplace->right_son;
        ToReplace->right_son = Tree->right_son;
        Tree->right_son = temp;
        ToReplace->right = remove(Tree->key, ToReplace->right_son);
    }
    else{
        node* temp = Tree;
        if(Tree->left == nullptr)
            Tree = Tree->right_son;
        else if(Tree->right == nullptr)
            Tree = Tree->left_son;
        delete temp;
        Size--;
    }
    if(!Tree)
        return Tree;

    Tree->Height = max(height(Tree->left_son), height(Tree->right_son))+1;

    if(height(Tree->left_son) - height(Tree->right_son) == 2)
    {
        // LL case
        if(height(Tree->left_son->left_son) - height(Tree->left_son->right_son) >= 0)
            return RotateRight(Tree);
            // LR case
        else {
            Tree->left_son = RotateLeft(Tree->left_son);
            Tree = RotateRight(Tree);
            return Tree;
        }
    }
    else if(height(Tree->left_son) - height(Tree->right_son) == -2)
    {
        // RR case
        if(height(Tree->right_son->left_son) - height(Tree->right_son->right_son) <= 0)
            return RotateLeft(Tree);
            // left right case
        else {
            Tree->right_son = RotateRight(Tree->right_son);
            Tree = RotateLeft(Tree);
            return Tree;
        }
    }
    return Tree;
}

template<class Key,class Info>
Info& BST<Key,Info>::FindNode(Key key,node* Tree){
    if(!Tree)
        throw KeyNotFound();
    if(key > Tree->key)
        FindNode(key,Tree->right_son);
    else if(key < Tree->key)
        FindNode(key,Tree->left_son);
    else{
        return Tree->info;
    }
}

template<class Key,class Info>
int BST<Key,Info>::GetSize(){
    return Size;
}

template<class Key,class Info>
int BST<Key,Info>::GetHeight(){
    return height(root);
}

template<class Key,class Info>
Info BST<Key,Info>::Find(Key key) {
    return FindNode(key,root);
}
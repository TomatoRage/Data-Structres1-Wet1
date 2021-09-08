#ifndef UNTITLED_BINARYSEARCHTREEIMP_H
#define UNTITLED_BINARYSEARCHTREEIMP_H

template<class Key,class Info>
BST<Key,Info>::BST():root(nullptr),iterator(nullptr),Size(0){}

template<class Key,class Info>
BST<Key,Info>::~BST<Key, Info>() {
    DeleteNode(root);
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key, Info>::insert(Key key, Info& info){
    return InsertNode(key,info,root);
}

template<class Key,class Info>
void BST<Key,Info>::remove(Key key) {
    root = RemoveNode(key,root);
}

template<class Key,class Info>
typename BST<Key,Info>::node*& BST<Key, Info>::InsertNode(Key key,Info& info, node*& NodeToAdd) {

    if(NodeToAdd == nullptr)
    {
        NodeToAdd = new node;
        NodeToAdd->key = key;
        NodeToAdd->info = info;
        NodeToAdd->Height = 1;
        NodeToAdd->left_son = NodeToAdd->right_son = NodeToAdd->father = nullptr;
        Size++;
    }
    else if(key == NodeToAdd->key)
        throw FailureException{};

    else if(key < NodeToAdd->key) {

        NodeToAdd->left_son = InsertNode(key,info,NodeToAdd->left_son);
        NodeToAdd->left_son->father = NodeToAdd;
        if (height(NodeToAdd->left_son) - height(NodeToAdd->right_son) == 2) {
            if (key < NodeToAdd->left_son->key)
                NodeToAdd = RotateRight(NodeToAdd);
            else {
                NodeToAdd->left_son = RotateLeft(NodeToAdd->left_son);
                NodeToAdd = RotateRight(NodeToAdd);
            }

        }
    }

    else if(key > NodeToAdd->key)
    {
        NodeToAdd->right_son = InsertNode(key,info,NodeToAdd->right_son);
        NodeToAdd->right_son->father = NodeToAdd;
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

    NodeToAdd->Height = max(height(NodeToAdd->left_son), height(NodeToAdd->right_son))+1;
    return NodeToAdd;
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::RotateRight(node *&Node) {

    node* TempNode = Node->left_son;
    Node->left_son = TempNode->right_son;
    if(Node->left_son)
        Node->left_son->father = Node;
    TempNode->right_son = Node;
    TempNode->father = Node->father;
    Node->father = TempNode;
    Node->Height = max(height(Node->left_son), height(Node->right_son))+1;
    TempNode->Height = max(height(TempNode->left_son), Node->Height)+1;
    return TempNode;

}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::RotateLeft(node *&Node){

    node* TempNode = Node->right_son;
    Node->right_son = TempNode->left_son;
    if(Node->right_son)
        Node->right_son->father = Node;
    TempNode->left_son = Node;
    TempNode->father = Node->father;
    Node->father = TempNode;
    Node->Height = max(height(Node->left_son), height(Node->right_son))+1;
    TempNode->Height = max(height(TempNode->right_son), Node->Height)+1 ;
    return TempNode;
}

template<class Key,class Info>
int BST<Key,Info>::height(node *Node) {
    int Right = 0;
    int Left = 0;
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
typename BST<Key,Info>::node* BST<Key,Info>::FindSmallestNode(node* Tree) {
    if(Tree == nullptr)
        return Tree;
    else if(Tree->left_son == nullptr)
        return Tree;
    return FindSmallestNode(Tree->left_son);
}

template<class Key,class Info>
typename BST<Key,Info>::node* BST<Key,Info>::RemoveNode(Key key, node* Tree) {

    if(Tree == nullptr)
        throw KeyNotFound();

    else if(key < Tree->key)
        Tree->left_son = RemoveNode(key, Tree->left_son);
    else if(key > Tree->key)
        Tree->right_son = RemoveNode(key, Tree->right_son);

    else if(Tree->left_son && Tree->right_son)
    {
        node* Temp = FindSmallestNode(Tree->right_son);
        Tree->key = Temp->key;
        Tree->info = Temp->info;
        Tree->right_son = RemoveNode(Tree->key,Tree->right_son);
    }
    else{
        node* temp = Tree;
        if(Tree->left_son == nullptr){
            Tree = Tree->right_son;
            if(Tree && temp->father){
                Tree->father = temp->father;
                if(Tree->father->right_son == temp)
                    Tree->father->right_son = Tree;
                else
                    Tree->father->left_son = temp;
            }
        }
        else if(Tree->right_son == nullptr){
            Tree = Tree->left_son;
            if(Tree && temp->father) {
                Tree->father = temp->father;
                if (Tree->father->right_son == temp)
                    Tree->father->right_son = Tree;
                else
                    Tree->father->left_son = temp;
            }
        }

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
        return FindNode(key,Tree->right_son);
    else if(key < Tree->key)
        return FindNode(key,Tree->left_son);
    return Tree->info;
}

template<class Key,class Info>
void BST<Key,Info>::DeleteNode(node*& ToDelete) {
    if(!ToDelete || Size == 0)
        return;
    DeleteNode(ToDelete->right_son);
    DeleteNode(ToDelete->left_son);
    Size--;
    delete ToDelete;
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
Info& BST<Key,Info>::Find(Key key) {
    return FindNode(key,root);
}

template<class Key,class Info>
void BST<Key,Info>::clear() {
    DeleteNode(root);
}

template<class Key,class Info>
void BST<Key, Info>::ResetIterator(){
    iterator = root;
    iterator = FindSmallestNode(iterator);
}

template<class Key,class Info>
Info& BST<Key, Info>::NextIteration(Key **key) {
   if(iterator == nullptr)
       throw FailureException{};
    **key = iterator->key;
    Info& Temp = iterator->info;
    if (iterator->right_son) {
        iterator = iterator->right_son;
        while (iterator->left_son) {
            iterator = iterator->left_son;
        }
    } else {
        while (iterator->father && iterator == iterator->father->right_son) {
            iterator = iterator->father;
        }
        iterator = iterator->father;
    }
    return Temp;
}

#endif //UNTITLED_BINARYSEARCHTREEIMP_H

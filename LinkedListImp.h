#ifndef LINKEDLISTIMP_H
#define LINKEDLISTIMP_H

template<class Key,class Info>
LinkedList<Key,Info>::LinkedList():head(nullptr),tail(nullptr),Size(0),Iterator(nullptr){}

template<class Key,class Info>
LinkedList<Key,Info>::~LinkedList<Key, Info>() {
    deleteNode(head);
}

template<class Key,class Info>
typename LinkedList<Key,Info>::node* LinkedList<Key,Info>::insert(Key key, Info info){

    node* Node = new node;

    Node->next = nullptr;
    Node->key = key;
    Node->info = info;
    Size++;

    if(head == nullptr && tail == nullptr){
        head = Node;
        tail = Node;
    }
    else{
        tail->next = Node;
        tail = Node;
    }
    return Node;
}

template<class Key,class Info>
void LinkedList<Key,Info>::remove(Key key){

    node* Prev,*CurrentNode = head;

    while(CurrentNode) {

        if (key != CurrentNode->key){
            Prev = CurrentNode;
            CurrentNode = CurrentNode->next;
        }
        else{
            if(CurrentNode == head && CurrentNode->next)
                head = CurrentNode->next;
            else if(CurrentNode == head){
                head = nullptr;
                tail = nullptr;
            }
            else{
                Prev->next = CurrentNode->next;
                if(CurrentNode == tail)
                    tail = Prev;
            }
            Size--;
            delete CurrentNode;
            return;
        }
    }
    throw KeyNotFound();
}

template<class Key,class Info>
int LinkedList<Key,Info>::GetSize() {
    return Size;
}

template<class Key,class Info>
Info& LinkedList<Key,Info>::Find(Key key) {
    node* CurrentNode = head;
    while(CurrentNode != nullptr){
        if(key != CurrentNode->key)
            CurrentNode = CurrentNode->next;
        else
            return CurrentNode->info;
    }
    throw KeyNotFound();
}

template<class Key,class Info>
void LinkedList<Key,Info>::clear() {
    deleteNode(head);
}

template<class Key,class Info>
void LinkedList<Key,Info>::deleteNode(node *ToDelete)  {
    if(ToDelete == nullptr || Size == 0)
        return;
    deleteNode(ToDelete->next);
    Size--;
    delete ToDelete;
}

template<class Key,class Info>
Info& LinkedList<Key,Info>::First(Key** key) {
    if(head == nullptr)
        *key = nullptr;
    **key = head->key;
    return head->info;
}

template<class Key,class Info>
Info& LinkedList<Key,Info>::Next(Key** key) {
    Iterator = Iterator->next;
    if(Iterator == nullptr)
        *key = nullptr;
    **key = Iterator->key;
    return Iterator->info;
}

#endif //LINKEDLISTIMP_H

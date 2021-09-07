#include "library1.h"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "iostream"

#define TREE

void *Init(){
    try {
#ifdef TREE
        auto DS = new BST<int,void*>();
#else
        LinkedList<int, void *>* DS = new LinkedList<int,void*>();
#endif
        return (void*)DS;

    }catch (std::bad_alloc& e){
        return nullptr;
    }
}

StatusType Add(void *DS, int key, void* value, void** node){
    if(!DS || !node)
        return INVALID_INPUT;
    try{
#ifdef TREE
        *node = (void*)((BST<int,void*>*)DS)->insert(key,value);
#else
        *node = (void*)((LinkedList<int,void*>*)DS)->insert(key,value);
#endif
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Find(void *DS, int key, void** value){
    if(!DS || !value)
        return INVALID_INPUT;
    try{
#ifdef TREE
        *value = ((BST<int,void*>*)DS)->Find(key);
#else
        *value = ((LinkedList<int,void*>*)DS)->Find(key);
#endif
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType Delete(void *DS, int key){
    if(!DS)
        return INVALID_INPUT;
    try{
#ifdef TREE
        ((BST<int,void*>*)DS)->remove(key);
#else
        ((LinkedList<int,void*>*)DS)->remove(key);
#endif
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType Size(void *DS, int *n){
    if(!DS || !n)
        return INVALID_INPUT;
    try{
#ifdef TREE
        *n = ((BST<int,void*>*)DS)->GetSize();
#else
        *n = ((LinkedList<int,void*>*)DS)->GetSize();
#endif
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void** DS){
    if(!DS)
        return;
#ifdef TREE
    delete *((BST<int,void*>**)DS);
#else
    ((LinkedList<int,void*>*)DS)->clear();
    delete *((LinkedList<int,void*>**)DS);
#endif
    DS = nullptr;
}
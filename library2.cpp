#include "Image.h"
#include "BinarySearchTree.h"
#include "library2.h"
#include "iostream"

void *Init(int segments){

    try{
        BST<int,Image*>* DS = new BST<int,Image*>();
        return (void*)DS;
    }catch(std::bad_alloc& e){
        return nullptr;
    }

}

StatusType AddImage(void *DS, int imageID){

    try{
        ((BST<int,Image*>*)DS)->insert(imageID,)
    }

}
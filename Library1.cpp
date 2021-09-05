#include "library1.h"
#include "BinarySearchTree.h"
#include "stdlib.h"
#include "iostream"

void *Init(){
    try {
        Dict<int, void *> DS;
    }catch (std::bad_alloc){
        return ALLOCATION_ERROR;
    }
}
#include "library1.h"
#include <cstdlib>

#ifndef TREE

typedef struct dict_t{
    int Key;
    void *Info;
    struct dict_t *next;
}*Dict;

typedef struct dummy_t{
    int NumOfElements;
    struct dict_t *start;
    struct dict_t *last;
}*DictStart;

void *Init(){

    DictStart Dictionary = (DictStart)malloc(sizeof(*Dictionary));

    if (Dictionary == nullptr)
        return nullptr;

    Dictionary->NumOfElements = 0;
    Dictionary->start = nullptr;
    Dictionary->last = nullptr;

    return (void*)Dictionary;

}

StatusType Add(void *DS, int key, void* value, void** node){

    if(DS == nullptr || node == nullptr)
        return INVALID_INPUT;

    Dict Element = (Dict)malloc(sizeof(*Element));

    if(Element == nullptr)
        return ALLOCATION_ERROR;

    Element->Key = key;
    Element->Info = value;
    Element->next = nullptr;

    *node = Element;

    if(((DictStart)DS)->last == nullptr)
        ((DictStart)DS)->start = Element;
    else
        ((DictStart)DS)->last->next = Element;

    ((DictStart)DS)->last = Element;
    ((DictStart)DS)->NumOfElements++;

    return SUCCESS;
}

StatusType Find(void *DS, int key, void** value){

    Dict ToCheck;

    if(DS == nullptr || value == nullptr)
        return INVALID_INPUT;

    ToCheck = ((DictStart)DS)->start;

    while(ToCheck != nullptr){

        if(ToCheck->Key == key) {
            *value = ToCheck->Info;
            return SUCCESS;
        }

        ToCheck = ToCheck->next;
    }

    return FAILURE;
}

StatusType Delete(void *DS, int key){

    Dict ToCheck;
    Dict Prev = nullptr;

    if(DS == nullptr){
        return INVALID_INPUT;
    }

    ToCheck = ((DictStart)DS)->start;

    while(ToCheck != nullptr) {

        if(ToCheck->Key == key) {

            if(Prev == nullptr)
                ((DictStart)DS)->start = ToCheck->next;

            if(ToCheck->next == nullptr) {
                ((DictStart) DS)->last = Prev;
                if(Prev != nullptr)
                    Prev->next = nullptr;
            }
            else if(Prev != nullptr){
                Prev->next = ToCheck->next;
            }

            ((DictStart)DS)->NumOfElements--;
            free(ToCheck);

            return SUCCESS;
        }

        Prev = ToCheck;
        ToCheck = ToCheck->next;
    }

    return FAILURE;
}

StatusType Size(void *DS, int *n){

    if(DS == nullptr || n == nullptr)
        return INVALID_INPUT;

    *n = ((DictStart)DS)->NumOfElements;

    return SUCCESS;
}

void Quit(void** DS){

    Dict ToCheck;

    if(*DS == nullptr)
        exit(0);

    ToCheck = ((DictStart)*DS)->start;

    free(*DS);
    *DS = nullptr;
    while(ToCheck != nullptr){
        Dict Temp = ToCheck->next;

        free(ToCheck);

        ToCheck = Temp;
    }
}

#endif
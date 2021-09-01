#include "library1.h"
#include "stdlib.h"

#ifdef TREE

// Tree Node
typedef struct node_t{
    int Key;
    void* Info;
    struct node_t* right_son;
    struct node_t* left_son;
    struct node_t* father;
}*Tree;

// Tree pointer contains tree size and tree start in case its empty points to null
typedef struct tree_head{
    int TreeSize;
    struct node_t* start;
}*Dict;

static void RotateTree(void* DS); // Balances Tree

void* Init(){

    Dict Dictionary = (Dict)malloc(sizeof(*Dictionary));

    if (Dictionary == nullptr)
        return nullptr;

    Dictionary->TreeSize = 0;
    Dictionary->start = nullptr;

    return Dictionary;
}

StatusType Add(void *DS, int key, void* value, void** node){

    Tree ToAddAfter = nullptr;

    if(DS == nullptr || node == nullptr)
        return INVALID_INPUT;

    Tree Node = (Tree) malloc(sizeof(*Node));

    if(Node == nullptr)
        return ALLOCATION_ERROR;

    Node->Info = value;
    Node->Key = key;
    Node->left_son= nullptr;
    Node->right_son = nullptr;
    Node->father = nullptr;

    ToAddAfter = ((Dict)DS)->start;

    if(ToAddAfter == nullptr){
        ((Dict)DS)->start = Node;
        ((Dict)DS)->TreeSize++;
        return SUCCESS;
    }

    while(ToAddAfter != nullptr){

        if(Node->Key > ToAddAfter->Key){

            if(ToAddAfter->right_son == nullptr){
                ToAddAfter->right_son = Node;
                Node->father = ToAddAfter->right_son;
                ((Dict)DS)->TreeSize++;
                RotateTree(DS);
                return SUCCESS;
            }
            else{
                ToAddAfter = ToAddAfter->right_son;
                continue;
            }

        }

        if(Node->Key < ToAddAfter->Key){

            if(ToAddAfter->left_son == nullptr){
                ToAddAfter->left_son = Node;
                Node->father = ToAddAfter->left_son;
                ((Dict)DS)->TreeSize++;
                RotateTree(DS);
                return SUCCESS;
            }
            else{
                ToAddAfter = ToAddAfter->left_son;
                continue;
            }

        }

    }

    return FAILURE;
}

static void RotateTree(void *DS){

}

#endif
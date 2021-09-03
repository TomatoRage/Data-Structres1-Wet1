#include "library1.h"
#include "stdlib.h"

#ifdef TREE

static enum rotation{
    LL = 0,
    LR = 1,
    RL = 2,
    RR = 3
};

typedef enum rotation Rotation;

// Tree Node
typedef struct node_t{
    int Key;
    int TreeHeight;
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

static void RotateTreeForAdd(void* DS,Tree added_node); // Balances Tree
static int Max(int x,int y); //Get Max Out Of Two Numbers
static void FreeTreeNode(Tree Node); //r=Recursive function used to free nodes

void* Init(){

    Dict Dictionary = (Dict)malloc(sizeof(*Dictionary));

    if (Dictionary == nullptr)
        return nullptr;

    Dictionary->TreeSize = 0;
    Dictionary->start = nullptr;

    return (void*)Dictionary;
}

StatusType Add(void *DS, int key, void* value, void** node){

    Tree ToAddAfter = nullptr;
    Tree FatherToGetHeight = nullptr;

    if(DS == nullptr || node == nullptr)
        return INVALID_INPUT;

    Tree Node = (Tree) malloc(sizeof(*Node));

    if(Node == nullptr)
        return ALLOCATION_ERROR;

    Node->Info = value;
    Node->Key = key;
    Node->TreeHeight = 1;
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
                break;
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
                break;
            }
            else{
                ToAddAfter = ToAddAfter->left_son;
                continue;
            }

        }

    }

   /* FatherToGetHeight = Node->father;

    while(FatherToGetHeight != nullptr){

        int RightSonHeight = 0;
        int LeftSonHeight = 0;

        if(FatherToGetHeight->right_son != nullptr)
            RightSonHeight = FatherToGetHeight->right_son->TreeHeight;
        if(FatherToGetHeight->left_son != nullptr)
            LeftSonHeight = FatherToGetHeight->left_son->TreeHeight;

        FatherToGetHeight->TreeHeight = Max(RightSonHeight,LeftSonHeight) + 1;

        FatherToGetHeight = FatherToGetHeight->father;

    }*/

    RotateTreeForAdd(DS,Node);

    return SUCCESS;
}

StatusType Find(void *DS, int key, void** value){

    Tree nextToCheck;

    if(DS == nullptr || value == nullptr)
        return INVALID_INPUT;

    nextToCheck = ((Dict)DS)->start;

    while(nextToCheck != nullptr){

        if(nextToCheck->Key == key){
            *value = nextToCheck->Info;
            return SUCCESS;
        }

        if(nextToCheck->Key > key)
            nextToCheck = nextToCheck->left_son;
        if(nextToCheck->Key < key)
            nextToCheck = nextToCheck->right_son;
    }
    return FAILURE;
}

StatusType Delete(void *DS, int key){

}

StatusType Size(void *DS, int *n){

    if(DS == nullptr || n == nullptr)
        return INVALID_INPUT;

    *n = ((Dict)DS)->TreeSize;

    return SUCCESS;
}

void Quit(void** DS){

    if(DS == nullptr)
        return;

    FreeTreeNode(((Dict)*DS)->start);
    free(*DS);

    return;
}

static void FreeTreeNode(Tree Node){

    if(Node == nullptr)
        return;

    FreeTreeNode(Node->left_son);
    FreeTreeNode(Node->right_son);
    free(Node);
}

static void RotateTreeForAdd(void *DS,Tree node_change){

    Tree father = node_change->father;
    Tree PrevSon;
    int PrevBF = 0;
    int BF;

    while(father != nullptr){

        int RightSonHeight = 0;
        int LeftSonHeight = 0;

        if(father->right_son != nullptr)
            RightSonHeight = father->right_son->TreeHeight;
        if(father->left_son != nullptr)
            LeftSonHeight = father->left_son->TreeHeight;

        BF = LeftSonHeight - RightSonHeight;

        if(father->TreeHeight == Max(RightSonHeight,LeftSonHeight) + 1 && !(BF == -2 || BF == 2)){
            break;
        }

        father->TreeHeight = Max(RightSonHeight,LeftSonHeight) + 1;

        if(BF == 2 || BF == -2){

        }

        PrevBF = BF;
        PrevSon = father;
        father = father->father;
    }

}


static int Max(int x,int y){
    if(x>y)
        return x;
    return y;
}

/*    Rotation Path;
    Tree father;

    father = node_change;

    if(((Dict)DS)->start->Key < node_change->Key){
        if(((Dict)DS)->start->left_son->Key < node_change->Key)
            Path = LL;
        else
            Path = LR;
    }
    else{
        if(((Dict)DS)->start->left_son->Key < node_change->Key)
            Path = RL;
        else
            Path = RR;
    }

    switch(Path) {
        case 0:

    }*/
#endif
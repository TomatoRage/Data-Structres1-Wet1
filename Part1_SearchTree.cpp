#include "library1.h"
#include "stdlib.h"
#include "assert.h"

#ifdef TREE

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

static void RotateTree(void* DS,Tree designated_node,int key); // Balances Tree When Adding or Deleting a Node And Updates Heights
static int Max(int x,int y); //Get Max Out Of Two Numbers
static void FreeTreeNode(Tree Node); //Recursive function used to free nodes
static void LLRotate(Tree root); // Does Right Rotation
static void RRRotate(Tree root); // Does Left Rotation

void* Init(){

    Dict Dictionary = (Dict)malloc(sizeof(*Dictionary));

    if (Dictionary == nullptr)
        return nullptr;

    Dictionary->TreeSize = 0;
    Dictionary->start = nullptr;

    return (void*)Dictionary;
}

StatusType Add(void *DS, int key, void* value, void** node){

    Tree ToAddAfter; // Father of added node

    if(DS == nullptr || node == nullptr)
        return INVALID_INPUT;

    Tree Node = (Tree) malloc(sizeof(*Node)); // Our added Node

    if(Node == nullptr)
        return ALLOCATION_ERROR;

    Node->Info = value;
    Node->Key = key;
    Node->TreeHeight = 1;
    Node->left_son= nullptr;
    Node->right_son = nullptr;
    Node->father = nullptr;

    ToAddAfter = ((Dict)DS)->start;

    //In case of Node being first root
    if(ToAddAfter == nullptr){
        ((Dict)DS)->start = Node;
        ((Dict)DS)->TreeSize++;
        return SUCCESS;
    }

    while(ToAddAfter != nullptr){

        if(Node->Key > ToAddAfter->Key){

            if(ToAddAfter->right_son == nullptr){
                ToAddAfter->right_son = Node;
                Node->father = ToAddAfter;
                ((Dict)DS)->TreeSize++;
                break;
            }
            else{
                ToAddAfter = ToAddAfter->right_son;
                continue;
            }

        }

        else if(Node->Key < ToAddAfter->Key){

            if(ToAddAfter->left_son == nullptr){
                ToAddAfter->left_son = Node;
                Node->father = ToAddAfter;
                ((Dict)DS)->TreeSize++;
                break;
            }
            else{
                ToAddAfter = ToAddAfter->left_son;
                continue;
            }

        }

    }

    RotateTree(DS,Node->father,key); // Balance Tree After Adding

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
        else if(nextToCheck->Key < key)
            nextToCheck = nextToCheck->right_son;
    }
    return FAILURE;
}

StatusType Delete(void *DS, int key){

    Tree ToDelete;

    if(DS == nullptr)
        return INVALID_INPUT;

    ToDelete = ((Dict)DS)->start;

     if(ToDelete == nullptr)
         return FAILURE;

    while(ToDelete != nullptr){

        if(ToDelete->Key == key){

            //Removes toDelete from the Tree

            if(ToDelete->right_son == nullptr && ToDelete->left_son == nullptr){
                if(ToDelete->father != nullptr) {
                    //In case toDelete is a leaf
                    if (ToDelete->father->right_son == ToDelete)
                        ToDelete->father->right_son = nullptr;
                    if (ToDelete->father->left_son == ToDelete)
                        ToDelete->father->left_son = nullptr;
                }
                else
                    //In case only ToDelete in the tree
                    ((Dict)DS)->start = nullptr;
            }
            else{
                if(ToDelete->right_son == nullptr){

                    if(ToDelete->father == nullptr)
                        //In case toDelete is the main root
                        ((Dict)DS)->start = ToDelete->left_son;
                    else{
                        if (ToDelete->father->right_son == ToDelete)
                            ToDelete->father->right_son = ToDelete->left_son;
                        if (ToDelete->father->left_son == ToDelete)
                            ToDelete->father->left_son = ToDelete->left_son;
                    }

                }
                else{
                    //In case toDelete is inner root replace the next least key
                    Tree Temp = ToDelete->right_son;

                    while(Temp->left_son != nullptr)
                        Temp = Temp->left_son;

                    ToDelete->Key = Temp->Key;
                    ToDelete->Info = Temp->Info;

                    if(Temp->left_son == nullptr && Temp->right_son == nullptr){
                        if(Temp->father->right_son == Temp)
                            Temp->father->right_son = nullptr;
                        if(Temp->father->left_son == Temp)
                            Temp->father->left_son = nullptr;
                    }
                    else{
                        if(ToDelete->right_son == Temp){
                            ToDelete->right_son = Temp->right_son;
                            Temp->right_son->father = ToDelete;
                        }
                        else{
                            Temp->father->left_son = Temp->right_son;
                            Temp->right_son->father = Temp->father;
                        }
                    }

                    ToDelete = Temp;
                }
            }

            //Balances Tree after removing toDelete from the Tree

            RotateTree(DS,ToDelete->father,key);
            ((Dict)DS)->TreeSize--;
            free(ToDelete);

            return SUCCESS;
        }

        if(ToDelete->Key > key)
            ToDelete = ToDelete->left_son;
        else if(ToDelete->Key < key)
            ToDelete = ToDelete->right_son;
    }
    return FAILURE;
}

StatusType Size(void *DS, int *n){

    if(DS == nullptr || n == nullptr)
        return INVALID_INPUT;

    *n = ((Dict)DS)->TreeSize;

    return SUCCESS;
}

void Quit(void** DS){

    // Frees each node then frees the pointer

    if(DS == nullptr)
        return;

    FreeTreeNode(((Dict)*DS)->start);
    free(*DS);

    *DS = nullptr;
}

static void FreeTreeNode(Tree Node){

    //Frees Post Order

    if(Node == nullptr)
        return;

    FreeTreeNode(Node->left_son);
    FreeTreeNode(Node->right_son);
    free(Node);
}

/** Function calculates BF from bottom to top if its 2 or -2 checks the wanted son BF and calls for rotate accordingly **/

static void RotateTree(void *DS,Tree designated_node,int key){

    Tree father = designated_node;
    int PrevBF;
    int BF;

    while(father != nullptr){

        int RightSonHeight = 0;
        int LeftSonHeight = 0;

        if(father->right_son != nullptr)
            RightSonHeight = father->right_son->TreeHeight;
        if(father->left_son != nullptr)
            LeftSonHeight = father->left_son->TreeHeight;

        BF = LeftSonHeight - RightSonHeight;

        assert(BF <= 2 && BF >= -2);

        if(BF == 2){

            RightSonHeight = 0;
            LeftSonHeight = 0;

            if(father->left_son->right_son != nullptr)
                RightSonHeight = father->left_son->right_son->TreeHeight;
            if(father->left_son->left_son != nullptr)
                LeftSonHeight = father->left_son->left_son->TreeHeight;

            PrevBF = LeftSonHeight-RightSonHeight;

            if(PrevBF >= 0){

                LLRotate(father);

            }
            else if(PrevBF == -1){

                RRRotate(father->left_son);
                LLRotate(father);

            }

        }
        else if(BF == -2){

            RightSonHeight = 0;
            LeftSonHeight = 0;

            if(father->right_son->right_son != nullptr)
                RightSonHeight = father->right_son->right_son->TreeHeight;
            if(father->right_son->left_son != nullptr)
                LeftSonHeight = father->right_son->left_son->TreeHeight;

            PrevBF = LeftSonHeight-RightSonHeight;

            if(PrevBF <= 0){
                RRRotate(father);
            }
            else if(PrevBF == -1){

                LLRotate(father->right_son);
                RRRotate(father);

            }
        }

        if(father->father == nullptr)
            ((Dict)DS)->start = father;
        father = father->father;
    }

}

static int Max(int x,int y){
    if(x>y)
        return x;
    return y;
}

static void LLRotate(Tree root){

    // Rotate LL

    Tree TempSon = root->left_son->right_son;
    Tree TempFather = root->left_son;
    root->left_son = TempSon;
    TempFather->right_son = root;
    TempFather->father = root->father;
    root->father = TempFather;
    root = TempFather;

    if(root->father != nullptr){
        if(root->father->right_son == root->right_son)
            root->father->right_son = root;
        if(root->father->left_son == root->right_son)
            root->father->left_son = root;
    }

    if(TempSon != nullptr)
        TempSon->father = root->right_son;

    // Fix Trees Heights

    int RightSonHeight = 0;
    int LeftSonHeight = 0;

    if(root->right_son->right_son != nullptr)
        RightSonHeight = root->right_son->right_son->TreeHeight;
    if(root->right_son->left_son != nullptr)
        LeftSonHeight = root->right_son->left_son->TreeHeight;

    root->right_son->TreeHeight = Max(RightSonHeight,LeftSonHeight) + 1;

    RightSonHeight = 0;
    LeftSonHeight = 0;

    if(root->right_son != nullptr)
        RightSonHeight = root->right_son->TreeHeight;
    if(root->left_son != nullptr)
        LeftSonHeight = root->left_son->TreeHeight;

    root->TreeHeight = Max(RightSonHeight,LeftSonHeight) + 1;
}

static void RRRotate(Tree root){

    // Rotate RR

    Tree TempSon = root->right_son->left_son;
    Tree TempFather = root->right_son;
    root->right_son = TempSon;
    TempFather->left_son = root;
    TempFather->father = root->father;
    root->father = TempFather;
    root = TempFather;

    if(root->father != nullptr){
        if(root->father->right_son == root->left_son)
            root->father->right_son = root;
        if(root->father->left_son == root->left_son)
            root->father->left_son = root;
    }

    if(TempSon != nullptr)
        TempSon->father = root->left_son;

    // Fix Trees Heights

    int RightSonHeight = 0;
    int LeftSonHeight = 0;

    if(root->left_son->right_son != nullptr)
        RightSonHeight = root->left_son->right_son->TreeHeight;
    if(root->left_son->left_son != nullptr)
        LeftSonHeight = root->left_son->left_son->TreeHeight;

    root->left_son->TreeHeight = Max(RightSonHeight,LeftSonHeight) + 1;

    RightSonHeight = 0;
    LeftSonHeight = 0;

    if(root->right_son != nullptr)
        RightSonHeight = root->right_son->TreeHeight;
    if(root->left_son != nullptr)
        LeftSonHeight = root->left_son->TreeHeight;

    root->TreeHeight = Max(RightSonHeight,LeftSonHeight) + 1;
}

#endif
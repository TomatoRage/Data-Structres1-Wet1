#include "ImageTagger.h"
#include "Image.h"
#include "library2.h"
#include "iostream"

void *Init(int segments){

    try{
       ImageTagger* DS = new ImageTagger(segments);
        return (void*)DS;
    }catch(std::bad_alloc& e){
        return nullptr;
    }

}

StatusType AddImage(void *DS, int imageID){

    if(!DS || imageID < 0)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->AddImage(imageID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch(...){
        return FAILURE;
    }
    return SUCCESS;

}

StatusType DeleteImage(void *DS, int imageID){

    if(!DS || imageID < 0)
        return INVALID_INPUT;
    try {
        ((ImageTagger *) DS)->DeleteImage(imageID);
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddLabel(void *DS, int imageID, int segmentID, int label){
    if(!DS || imageID <= 0 || segmentID < 0 || label <= 0)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->LabelImage(imageID,segmentID,label);
    }catch(std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }catch(Image::InvalidInput&){
        return INVALID_INPUT;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label){
    if(!DS || !label || segmentID < 0 || imageID <= 0)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->GetLabel(imageID,segmentID,label);
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(Image::InvalidInput&){
        return INVALID_INPUT;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType DeleteLabel(void *DS, int imageID, int segmentID){
    if(!DS || imageID <= 0 || segmentID < 0)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->RemoveLabel(imageID,segmentID);
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(Image::InvalidInput&){
        return INVALID_INPUT;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments, int *numOfSegments){
    if(!DS || !segments || !numOfSegments || imageID <= 0)
        return INVALID_INPUT;
    try{
        *numOfSegments = ((ImageTagger*)DS)->GetAllUnlabeled(imageID,segments);
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(Image::InvalidInput&){
        return INVALID_INPUT;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int *numOfSegments){
    if(!DS || !images || !segments || !numOfSegments)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->GetAllByLabel(label,images,segments);
    }catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(Image::InvalidInput&){
        return INVALID_INPUT;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void** DS){
    if(!DS)
        return;
    delete *(ImageTagger**)DS;
    DS = nullptr;
}
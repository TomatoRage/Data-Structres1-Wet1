#include "Image.h"
#include <stdlib.h>

Image::Image(int segments){

    NumOfSegments = segments;
    Segments = new int[segments];

    for(int i = 0; i < segments;i++){
        this->UnLabeledSegments.insert(i,-1);
        Segments[i] = -1;
    }

}

Image::~Image() {
    UnLabeledSegments.clear();
    delete[] Segments;
}

void Image::addLabel(int SegmentID, int Label) {
    if(SegmentID > NumOfSegments || SegmentID < 0)
        throw InvalidInput();
    if(Segments[SegmentID] != -1)
        throw AlreadyLabeled();

    Segments[SegmentID] = Label;
    UnLabeledSegments.remove(SegmentID);
}

void Image::removeLabel(int SegmentID) {
    if(SegmentID > NumOfSegments || SegmentID < 0)
        throw InvalidInput();
    if(Segments[SegmentID] == -1)
        throw SegmentUnlabeled();
    Segments[SegmentID] = -1;
    UnLabeledSegments.insert(SegmentID,-1);
}

int Image::GetLabel(int SegmentID) {
    if(SegmentID > NumOfSegments || SegmentID < 0)
        throw InvalidInput();
    if(Segments[SegmentID] == 1)
        throw SegmentUnlabeled();
    return Segments[SegmentID];
}

int Image::GetNumberOfLabeledSegments() {
    return NumOfSegments-UnLabeledSegments.GetSize();
}

int Image::GetUnlabeledSegments(int** UnlabeledArray) {
    int key,NumberOfSegments = 0;
    int* keyptr = &key;

    if(GetNumberOfLabeledSegments() == NumOfSegments)
        throw ImageFullyLabeled();

    NumberOfSegments = UnLabeledSegments.GetSize();
    int* Array = (int*) malloc(sizeof(int)*NumberOfSegments);
    UnLabeledSegments.First(&keyptr);

    if(keyptr == nullptr)
        throw ImageFullyLabeled();

    for(int i = 0; i < UnLabeledSegments.GetSize();i++){
        Array[i] = key;
        UnLabeledSegments.Next(&keyptr);
        if(keyptr == nullptr)
            break;
    }

    *UnlabeledArray = Array;

    return NumberOfSegments;
}

int Image::GetLabeledSegments(int* LabeledSegmentsArray, int Label) {
    int count = 0;
    for(int i = 0; i < NumOfSegments;i++){
        if(Segments[i] == -1)
            continue;
        if(Segments[i] != Label)
            continue;
        LabeledSegmentsArray[count] = i;
        count++;
    }
    return count;
}


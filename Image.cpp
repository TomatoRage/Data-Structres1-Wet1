#include "Image.h"
#include <stdlib.h>

Image::Image(int segments):Segments(new int[segments]),NumOfSegments(segments){

    for(int i = 0; i < segments;i++){
        this->UnLabeledSegments.insert(i,-1);
        this->Segments[i] = -1;
    }

}

Image::Image():Segments(nullptr),NumOfSegments(0) {}

Image::Image(Image& other){
    int Key,temp;
    int* Key_ptr = &Key;
    NumOfSegments = other.NumOfSegments;
    Segments = new int[NumOfSegments];
    for(int i = 0; i < NumOfSegments;i++)
        Segments[i] = other.Segments[i];
    temp = other.UnLabeledSegments.First(&Key_ptr);
    if(Key_ptr)
        UnLabeledSegments.insert(Key,temp);
    for(int i=1;i < other.UnLabeledSegments.GetSize();i++){
        temp = other.UnLabeledSegments.Next(&Key_ptr);
        if(Key_ptr)
            UnLabeledSegments.insert(Key,temp);
    }
}

void Image::SetSegmentSize(int segments) {
    if(segments <= 0 || NumOfSegments != 0)
        return;
    Segments = new int[segments];
    NumOfSegments = segments;
    for(int i = 0; i < NumOfSegments;i++)
        Segments[i] = -1;
}

Image::~Image() {
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
    int x = Segments[SegmentID];
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
    int key,i,NumberOfSegments = 0;
    int* keyptr = &key;

    if(GetNumberOfLabeledSegments() == NumOfSegments)
        throw ImageFullyLabeled();

    NumberOfSegments = UnLabeledSegments.GetSize();
    int* Array = (int*) malloc(sizeof(int)*NumberOfSegments);
    UnLabeledSegments.First(&keyptr);

    if(keyptr == nullptr)
        throw ImageFullyLabeled();

    for(i = 0; i < UnLabeledSegments.GetSize()-1;i++){
        Array[i] = key;
        UnLabeledSegments.Next(&keyptr);
        if(keyptr == nullptr)
            break;
    }

    Array[i] = key;

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


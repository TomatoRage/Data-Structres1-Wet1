#ifndef IMAGE_H
#define IMAGE_H

#include "LinkedList.h"

class Image{

    LinkedList<int,int> UnLabeledSegments;
    int* Segments;
    int NumOfSegments;

public:

    explicit Image(int segments);
    ~Image();
    void addLabel(int SegmentID,int Label);
    void removeLabel(int SegmentID);
    int GetLabel(int SegmentID);
    int GetNumberOfLabeledSegments();
    int GetUnlabeledSegments(int** UnlabeledArray);
    int GetLabeledSegments(int* LabeledSegmentsArray,int Label);

    class FailureException{};
    class AlreadyLabeled:public FailureException{};
    class SegmentUnlabeled:public FailureException{};
    class ImageFullyLabeled:public FailureException{};
    class InvalidInput:public FailureException{};
};

#endif //IMAGE_H

#ifndef IMAGETAGGER_H
#define IMAGETAGGER_H

#include "Image.h"
#include "BinarySearchTree.h"

class ImageTagger {

    BST<int,Image> ImageContainer;
    int ImageSegments;

public:

    explicit ImageTagger(int segments);
    void AddImage(int ImageID);
    void DeleteImage(int ImageID);
    void LabelImage(int ImageID,int segmentID,int Label);
    void GetLabel(int ImageID,int segmentID,int* label);
    void RemoveLabel(int ImageID,int SegmentID);
    int GetAllUnlabeled(int ImageID,int** segments);
    int GetAllByLabel(int label,int** ImagesArray,int** SegmentsArray);
};


#endif //IMAGETAGGER_H

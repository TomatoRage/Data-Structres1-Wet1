#include <cstdlib>
#include "iostream"
#include "ImageTagger.h"

ImageTagger::ImageTagger(int segments):ImageSegments(segments) {}

void ImageTagger::AddImage(int ImageID) {
    ImageContainer.insert(ImageID,(new Image(ImageSegments)));
}

void ImageTagger::DeleteImage(int ImageID) {
    Image *Temp = ImageContainer.Find(ImageID);
    ImageContainer.remove(ImageID);
    delete Temp;
}

void ImageTagger::LabelImage(int ImageID, int segmentID, int Label) {
    Image *Temp = ImageContainer.Find(ImageID);
    Temp->addLabel(segmentID,Label);
}

void ImageTagger::GetLabel(int ImageID, int segmentID, int *label) {
    Image* Temp = ImageContainer.Find(ImageID);
    *label = Temp->GetLabel(segmentID);
}

void ImageTagger::RemoveLabel(int ImageID, int SegmentID) {
    Image* Temp = ImageContainer.Find(ImageID);
    Temp->removeLabel(SegmentID);
}

int ImageTagger::GetAllUnlabeled(int ImageID,int** segments) {
    Image* Temp = ImageContainer.Find(ImageID);
    return Temp->GetUnlabeledSegments(segments);
}

int ImageTagger::GetAllByLabel(int label,int** ImagesArray, int** SegmentsArray) {
    int ImageID,TotalLabeled = 0,NumLabeled;
    int* key_ptr = &ImageID;
    int* segments = (int*)malloc(sizeof(int)*ImageSegments*ImageContainer.GetSize());
    int* Images = (int*)malloc(sizeof(int)*ImageSegments*ImageContainer.GetSize());
    int* Temp = (int*)malloc(sizeof(int)*ImageSegments);

    if(!segments || !Images || !Temp)
        throw std::bad_alloc();

    ImageContainer.ResetIterator();

    for(int i = 0; i < ImageContainer.GetSize(); i++){

        for(int j = 0; j < ImageSegments; j++){
            Temp[j] = -1;
        }

        Image* currentimage = ImageContainer.NextIteration(&key_ptr);
        NumLabeled = currentimage->GetLabeledSegments(Temp,label);

        for(int k = TotalLabeled; k < TotalLabeled+NumLabeled;k++){
            segments[k] = Temp[k-TotalLabeled];
            Images[k] = ImageID;
        }

        TotalLabeled += NumLabeled;
    }

    realloc(segments,sizeof(int)*TotalLabeled);
    realloc(Images,sizeof(int)*TotalLabeled);
    free(Temp);

    if(!(segments || Images))
        throw std::bad_alloc();

    *ImagesArray = Images;
    *SegmentsArray = segments;

    return TotalLabeled;
}

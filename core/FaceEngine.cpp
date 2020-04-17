#include <iostream>
#include <sstream>
#include "FaceEngine.h"

using namespace sf2cs;
FaceInfoArray FaceEngine::detectFace(ImageData img) {
    return FD.detect(img);
}

FaceInfo FaceEngine::detectFace(ImageData img, int index) {
    SeetaFaceInfoArray faces=detectFace(img);
    if(index>=faces.size){
        return faces.data[faces.size-1];
    }
    else{
        return faces.data[index];
    }
}

PointFloatArray FaceEngine::detectPoints(const ImageData &image, const Rect &face) {
    PointFloatArray  ret{
            .data= new PointFloat[PD.number()],
            .size= PD.number(),
    };
    PD.mark( image, face, ret.data);
    return ret;
}

PointFloatArray FaceEngine::detectPoints(const ImageData &image, const FaceInfo &face) {
    return detectPoints(image,face.pos);
}

PointFloatArray FaceEngine::detectPoints(const ImageData &image) {
    FaceInfo  face = detectFace(image, 0);
    return detectPoints(image,face);
}

float FaceEngine::compare(const ImageData &image1, const Rect &face1, const ImageData &image2, const Rect &face2) {
    auto points1 = detectPoints( image1, face1 );
    auto points2 = detectPoints( image2, face2 );
    return FDB.Compare( image1, points1.data, image2, points2.data );
}

float
FaceEngine::compare(const ImageData &image1, const FaceInfo &face1, const ImageData &image2, const FaceInfo &face2) {
    return compare(image1,face1.pos,image2,face2.pos);
}

float FaceEngine::compare(const ImageData &image1, const ImageData &image2) {
    auto face1=detectFace(image1,0);
    auto face2= detectFace(image2,0);
    return compare(image1,face1,image2,face2);
}

float FaceEngine::compareByCroppedFace(const ImageData &image1, const ImageData &image2) {
    return FDB.CompareByCroppedFace(image1,image2);
}

ImageData FaceEngine::crop(const ImageData &image, const PointFloat *points) {
    int width= FDB.GetCropFaceWidth();
    int height=FDB.GetCropFaceHeight();
    int channels=FDB.GetCropFaceChannels();
    ImageData imageData{
        .width=width,
        .height=height,
        .channels=channels,
        .data= new unsigned  char[width*height*channels],
    };
    bool flag= FDB.CropFace(image,points,imageData);
    if(flag){
        return imageData;
    }
    else{
        return ImageData{};
    }
}

int FaceEngine::registerByCroppedFace(const ImageData &faceImage) {
    return FDB.RegisterByCroppedFace(faceImage);
}

QueryResult FaceEngine::queryByCroppedFace(const ImageData &faceImage) {
    QueryResult queryResult{};
    queryResult.index= FDB.QueryByCroppedFace(faceImage,&(queryResult.score));
    return queryResult;
}

QueryResultArray FaceEngine::queryTopByCroppedFace(const ImageData &faceImage, int n) {
    QueryResultArray queryResultArray{
        .data=new QueryResult[n],
    };
    long int *tempIndex= new long int[n];
    float * tempScore=new float[n];
    int size=FDB.QueryTopByCroppedFace(faceImage,n,tempIndex,tempScore);
    for(int i=0;i<size;i++){
        queryResultArray.data[i].index=tempIndex[i];
        queryResultArray.data[i].score=tempScore[i];
    }
    queryResultArray.size=size;
    delete tempIndex;
    delete tempScore;
    return  queryResultArray;
}

QueryResultArray FaceEngine::queryAboveByCroppedFace(const ImageData &faceImage, float threshold, int n) {
    QueryResultArray queryResultArray{
            .data=new QueryResult[n],
    };
    long int *tempIndex= new long int[n];
    float * tempScore=new float[n];
    int size=FDB.QueryAboveByCroppedFace(faceImage,threshold, n,tempIndex,tempScore);
    for(int i=0;i<size;i++){
        queryResultArray.data[i].index=tempIndex[i];
        queryResultArray.data[i].score=tempScore[i];
    }
    queryResultArray.size=size;
    delete[] tempIndex;
    delete[] tempScore;
    return  queryResultArray;
}

int FaceEngine::count() {
    return FDB.Count();
}

void FaceEngine::clear() {
    FDB.Clear();
}
size_t writeFunction( void *obj, const char *data, size_t length ){
   FaceDataBaseData* faceDataBaseData=  (FaceDataBaseData*)obj;
   if(faceDataBaseData->size==0){
       faceDataBaseData->data= (char*) std::malloc(length);
   }else{
       faceDataBaseData->data=(char *)std::realloc(faceDataBaseData->data,(faceDataBaseData->size+length));
   }
    std::stringstream stringStream;
    stringStream.write(data,length);
    stringStream.read(faceDataBaseData->data+faceDataBaseData->size,length);
    faceDataBaseData->size+=length;
    faceDataBaseData->data[faceDataBaseData->size]='\0';
    return length;
}
FaceDataBaseData FaceEngine::save() {
    FaceDataBaseData faceDataBaseData{
        .data=nullptr,
        .size=0,
    };
    seeta::CStreamWriter cStreamWriter(writeFunction, &faceDataBaseData);
    bool  flag=FDB.Save(cStreamWriter);
    if(flag){
        return faceDataBaseData;
    }
    else{
        return FaceDataBaseData{};
    }
}

size_t readFunction( void *obj, char *data, size_t length ){

    FaceDataBaseData *faceDataBaseData=(FaceDataBaseData*)obj;
    if(faceDataBaseData->index>=faceDataBaseData->size){
        return 0;
    }
    std::stringstream stringStream;
    stringStream.write(faceDataBaseData->data+faceDataBaseData->index,length);
    stringStream.read(data,length);
    faceDataBaseData->index+=length;
    return length;
}

bool FaceEngine::load(FaceDataBaseData faceDataBaseData) {
    seeta::CStreamReader cStreamReader(readFunction,&faceDataBaseData);
    return FDB.Load(cStreamReader);
}

void FaceEngine::set(int property, double value) {
    seeta::FaceDetector::Property  enumProperty= static_cast<seeta::FaceDetector::Property >(property);
    FD.set(enumProperty,value);
}

double FaceEngine::get(int property) {
    seeta::FaceDetector::Property  enumProperty= static_cast<seeta::FaceDetector::Property >(property);
    return FD.get(enumProperty);
}

bool FaceEngine::deleteByFDB(int index) {
    return FDB.Delete(index);
}


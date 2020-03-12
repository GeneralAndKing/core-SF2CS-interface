
#include <seeta/FaceDetector.h>
#include <seeta/FaceLandmarker.h>
#include <seeta/FaceDatabase.h>
#include <SF2CSStruct.h>

 namespace sf2cs{
     class FaceEngine{
     public:
         FaceEngine(const seeta::ModelSetting &FDModel, const seeta::ModelSetting &PDModel, const seeta::ModelSetting &FRModel,
                 int coreWidth,int coreHeight)
         :FD(FDModel,coreWidth,coreHeight),PD(PDModel),FDB(FRModel){}

         FaceInfoArray detectFace(ImageData img);

         FaceInfo detectFace(ImageData img, int index);

         PointFloatArray detectPoints(const ImageData &image, const Rect &face );

         PointFloatArray detectPoints(const ImageData &image, const FaceInfo &face );

         PointFloatArray detectPoints(const ImageData &image );

         ImageData  crop(const ImageData & image, const PointFloat  *points);

         int registerByCroppedFace(const ImageData &faceImage);

         float compare(
                 const ImageData &image1, const Rect &face1,
                 const ImageData &image2, const Rect &face2 );

         float compare(
                 const ImageData &image1, const FaceInfo &face1,
                 const ImageData &image2, const FaceInfo &face2 );

         float compare(const ImageData &image1, const ImageData &image2 );

         float compareByCroppedFace(const ImageData& image1, const ImageData & image2);

         QueryResult queryByCroppedFace(const ImageData& faceImage);

         QueryResultArray queryTopByCroppedFace(const ImageData& faceImage,int n);

         QueryResultArray queryAboveByCroppedFace(const ImageData& faceImage, float threshold,int n);

         int count();

         void clear();

         FaceDataBaseData save();

         bool load(FaceDataBaseData faceDataBaseData);

         void  set(int property, double value);

         double get(int property);

     private:
         seeta::FaceDetector FD;
         seeta::FaceLandmarker  PD;
         seeta::FaceDatabase FDB;
     };
 }




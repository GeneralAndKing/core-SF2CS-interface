//
// Created by bugrui on 2020/2/9.
//

#ifndef CORE_SF2CS_INTERFACE_SF2CSSTRUCT_H
#define CORE_SF2CS_INTERFACE_SF2CSSTRUCT_H

#include <seeta/CStruct.h>
#include <seeta/CFaceInfo.h>

typedef SeetaPointF  PointFloat;
typedef SeetaFaceInfoArray FaceInfoArray;
typedef SeetaImageData ImageData;
typedef SeetaRect Rect;
typedef SeetaFaceInfo FaceInfo;
struct PointFloatArray{
    PointFloat *data;
    int size;
};
struct QueryResult{
    int index;
    float score;
};
struct QueryResultArray{
    QueryResult * data;
    int size;
};

struct FaceDataBaseData{
    char * data;
    int size;
    int index;
};

#endif //CORE_SF2CS_INTERFACE_SF2CSSTRUCT_H


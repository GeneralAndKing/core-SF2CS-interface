#include <JNIHelper.h>
#include <string>
#include <iostream>

using namespace std;

static ImageDataFieldID _ImageDataFieldID("in/bugr/jni/model/ImageData");
static RectFieldID _RectFieldID("in/bugr/jni/model/Rect");
static FaceInfoFieldID _FaceInfoFieldID("in/bugr/jni/model/FaceInfo");
static FaceInfoArrayFieldID _FaceInfoArrayFieldID("in/bugr/jni/model/FaceInfoArray");
static PointFloatArrayFieldID _PointFloatArrayFieldID("in/bugr/jni/model/PointFloatArray");
static PointFloatFieldID _PointFloatFieldID("in/bugr/jni/model/PointFloat");
static QueryResultFieldID _QueryResultFieldID("in/bugr/jni/model/QueryResult");
static QueryResultArrayFieldID _QueryResultArrayFieldID("in/bugr/jni/model/QueryResultArray");

static FaceDataBaseDataFieldID _FaceDataBaseDataFieldID("in/bugr/jni/model/FaceDataBaseData");
JNIHelper::JNIHelper()= default;
JNIHelper::~JNIHelper()= default;

/*
 * 将java的SeetaImageData对象转成C++的SeetaImageData
 */
ImageData JNIHelper::toImageData(JNIEnv *env, jobject jImg){
    ImageDataFieldID field = getImageDataFieldID(env);

    ImageData imgData;
    jbyteArray jBytes = (jbyteArray)env->GetObjectField(jImg, field.data);
    imgData.data = (unsigned char*)env->GetByteArrayElements(jBytes, 0);
    imgData.width = env->GetIntField(jImg, field.width);
    imgData.height = env->GetIntField(jImg, field.height);
    imgData.channels = env->GetIntField(jImg, field.channels);
    env->DeleteLocalRef(jBytes);
    return imgData;
}

Rect JNIHelper::toRect(JNIEnv *env, jobject rectObject) {
    RectFieldID field = getRectFieldID(env);
    return  Rect{
        .x=env->GetIntField(rectObject, field.x),
        .y=env->GetIntField(rectObject,field.y),
        .width=env->GetIntField(rectObject,field.width),
        .height=env->GetIntField(rectObject,field.height),
    };
}


PointFloatArray JNIHelper::toPointFloatArray(JNIEnv *env, jobject pointFloatArrayObject) {
    PointFloatArrayFieldID pointFloatArrayFieldID= getPointFloatArrayFieldID(env);
    PointFloatFieldID pointFloatFieldID=getPointFloatFieldID(env);
    int size=env->GetIntField(pointFloatArrayObject,pointFloatArrayFieldID.size);
    auto *data=new PointFloat[size];
    auto  pointFloats=  (jobjectArray)env->GetObjectField(pointFloatArrayObject,pointFloatArrayFieldID.pointFloats);
    for(int i=0;i<size;i++){
        jobject  pointFloat=env->GetObjectArrayElement(pointFloats,i);
        data[i].x=env->GetDoubleField(pointFloat,pointFloatFieldID.x);
        data[i].y=env->GetDoubleField(pointFloat,pointFloatFieldID.y);
    }
    return PointFloatArray{
        .data=data,
        .size=size,
    };
}

FaceDataBaseData JNIHelper::toFaceDataBaseData(JNIEnv *env, jobject faceDataBaseDataObject) {
    FaceDataBaseDataFieldID faceDataBaseDataFieldID = getFaceDataBaseDataFieldID(env);
    FaceDataBaseData faceDataBaseData{};
    auto jBytes = (jbyteArray)env->GetObjectField(faceDataBaseDataObject, faceDataBaseDataFieldID.data);
    faceDataBaseData.data = (char*)env->GetByteArrayElements(jBytes, 0);
    faceDataBaseData.size = env->GetIntField(faceDataBaseDataObject, faceDataBaseDataFieldID.size);
    faceDataBaseData.index=0;
    env->DeleteLocalRef(jBytes);
    return faceDataBaseData;
}

ImageDataFieldID JNIHelper::getImageDataFieldID(JNIEnv *env) {
    //printf("\nget SeetaImageDataFieldID...\n");
    if (!_ImageDataFieldID.init) {
        //printf("init SeetaImageDataFieldID...\n");
        //获取SeetaImageData java对象
        jclass clazz = env->FindClass(_ImageDataFieldID.className);
        _ImageDataFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        //获取SeetaImageData对象的属性
        _ImageDataFieldID.data = env->GetFieldID(clazz, "data", "[B");
        _ImageDataFieldID.width = env->GetFieldID(clazz, "width", "I");
        _ImageDataFieldID.height = env->GetFieldID(clazz, "height", "I");
        _ImageDataFieldID.channels = env->GetFieldID(clazz, "channels", "I");

        //初始化完成
        _ImageDataFieldID.init = true;
    }
    return _ImageDataFieldID;
}

RectFieldID JNIHelper::getRectFieldID(JNIEnv *env) {
    //printf("get RectFieldID...\n");
    if (!_RectFieldID.init) {
        //printf("init RectFieldID...\n");
        //获取SeetaRect java对象
        jclass clazz = env->FindClass(_RectFieldID.className);
        //获取默认构造方法
        _RectFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        //获取SeetaRect对象的属性
        _RectFieldID.x = env->GetFieldID(clazz, "x", "I");
        _RectFieldID.y = env->GetFieldID(clazz, "y", "I");
        _RectFieldID.width = env->GetFieldID(clazz, "width", "I");
        _RectFieldID.height = env->GetFieldID(clazz, "height", "I");

        //初始化完成
        _RectFieldID.init = true;
    }
    return _RectFieldID;
}

FaceInfoFieldID JNIHelper::getFaceInfoFieldID(JNIEnv *env) {
    if(!_FaceInfoFieldID.init){
        jclass clazz = env->FindClass(_FaceInfoFieldID.className);
        //获取默认构造方法
        _FaceInfoFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        //获取SeetaRect对象的属性
        _FaceInfoFieldID.rect = env->GetFieldID(clazz, "rect", "Lin/bugr/jni/model/Rect;");
        _FaceInfoFieldID.score = env->GetFieldID(clazz, "score", "F");
        //初始化完成
        _FaceInfoFieldID.init = true;
    }
    return _FaceInfoFieldID;
}

FaceInfoArrayFieldID JNIHelper::getFaceInfoArrayFieldID(JNIEnv *env){
    if(!_FaceInfoArrayFieldID.init){
        jclass clazz = env->FindClass(_FaceInfoArrayFieldID.className);
        //获取默认构造方法
        _FaceInfoArrayFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        //获取SeetaRect对象的属性
        _FaceInfoArrayFieldID.faceInfos = env->GetFieldID(clazz, "faceInfos", "[Lin/bugr/jni/model/FaceInfo;");
        _FaceInfoArrayFieldID.size = env->GetFieldID(clazz, "size", "I");
        //初始化完成
        _FaceInfoArrayFieldID.init = true;
    }
    return _FaceInfoArrayFieldID;
}

PointFloatArrayFieldID JNIHelper::getPointFloatArrayFieldID(JNIEnv *env) {
    if(!_PointFloatArrayFieldID.init){
        jclass clazz=env->FindClass(_PointFloatArrayFieldID.className);
        _PointFloatArrayFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        _PointFloatArrayFieldID.pointFloats=env->GetFieldID(clazz,"pointFloats","[Lin/bugr/jni/model/PointFloat;");
        _PointFloatArrayFieldID.size = env->GetFieldID(clazz, "size", "I");
        _PointFloatArrayFieldID.init= true;
    }
    return _PointFloatArrayFieldID;
}

PointFloatFieldID JNIHelper::getPointFloatFieldID(JNIEnv *env) {
    if (!_PointFloatFieldID.init) {
        jclass clazz = env->FindClass(_PointFloatFieldID.className);
        _PointFloatFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        _PointFloatFieldID.x = env->GetFieldID(clazz, "x", "D");
        _PointFloatFieldID.y = env->GetFieldID(clazz, "y", "D");

        _PointFloatFieldID.init = true;
    }
    return _PointFloatFieldID;
}

QueryResultFieldID JNIHelper::getQueryResultFieldID(JNIEnv *env) {
    if(!_QueryResultFieldID.init){
        jclass clazz = env->FindClass(_QueryResultFieldID.className);
        _QueryResultFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        _QueryResultFieldID.index = env->GetFieldID(clazz, "index", "I");
        _QueryResultFieldID.score = env->GetFieldID(clazz, "score", "F");
        _QueryResultFieldID.init = true;
    }
    return _QueryResultFieldID;
}

QueryResultArrayFieldID JNIHelper::getQueryResultArrayFieldID(JNIEnv *env) {
    if(!_QueryResultArrayFieldID.init){
        jclass clazz=env->FindClass(_QueryResultArrayFieldID.className);
        _QueryResultArrayFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        _QueryResultArrayFieldID.queryResults=env->GetFieldID(clazz,"queryResults","[Lin/bugr/jni/model/QueryResult;");
        _QueryResultArrayFieldID.size = env->GetFieldID(clazz, "size", "I");
        _QueryResultArrayFieldID.init= true;
    }
    return _QueryResultArrayFieldID;
}

FaceDataBaseDataFieldID JNIHelper::getFaceDataBaseDataFieldID(JNIEnv *env) {
    if(!_FaceDataBaseDataFieldID.init){
        jclass clazz=env->FindClass(_FaceDataBaseDataFieldID.className);
        _FaceDataBaseDataFieldID.constructor = env->GetMethodID(clazz, "<init>", "()V");
        _FaceDataBaseDataFieldID.data=env->GetFieldID(clazz,"data","[B");
        _FaceDataBaseDataFieldID.size = env->GetFieldID(clazz, "size", "I");
        _FaceDataBaseDataFieldID.init= true;
    }
    return _FaceDataBaseDataFieldID;
}


jobject JNIHelper::newObject(JNIEnv * env, JClassDef classDef){
    jclass clazz = env->FindClass(classDef.className);
    return env->NewObject(clazz, classDef.constructor);
}

jobject JNIHelper::toFaceInfoObject(JNIEnv *env, FaceInfoArray faceInfoArray,int index) {
    if(faceInfoArray.size<index){
        return nullptr;
    }
    RectFieldID rectFieldID = getRectFieldID(env);
    jobject rectObject=newObject(env,rectFieldID);
    SeetaFaceInfo faceInfo= faceInfoArray.data[index];
    env->SetIntField(rectObject,rectFieldID.x,faceInfo.pos.x);
    env->SetIntField(rectObject,rectFieldID.y,faceInfo.pos.y);
    env->SetIntField(rectObject,rectFieldID.width,faceInfo.pos.width);
    env->SetIntField(rectObject,rectFieldID.height,faceInfo.pos.height);
     FaceInfoFieldID faceInfoFieldID=  getFaceInfoFieldID(env);
    jobject faceInfoObject= newObject(env,faceInfoFieldID);

    env->SetObjectField(faceInfoObject,faceInfoFieldID.rect,rectObject);
    env->SetFloatField(faceInfoObject,faceInfoFieldID.score,faceInfo.score);
    return faceInfoObject;
}

jobject JNIHelper::toFaceInfoArrayObject(JNIEnv *env, FaceInfoArray faceInfoArray) {
    if (faceInfoArray.size<=0){
        return nullptr;
    }
    FaceInfoFieldID faceInfoFieldID=getFaceInfoFieldID(env);
    jobjectArray  faceInfoArrayObjects= newObjectArray(env,faceInfoFieldID,faceInfoArray.size);
    for(int i=0;i<faceInfoArray.size;i++){
        jobject faceInfoObject= toFaceInfoObject(env,faceInfoArray,i);
        //添加到对象数组
        env->SetObjectArrayElement(faceInfoArrayObjects, i, faceInfoObject);
        env->DeleteLocalRef(faceInfoObject);
    }
    FaceInfoArrayFieldID faceInfoArrayFieldID= getFaceInfoArrayFieldID(env);
    jobject  faceInfoArrayObject =newObject(env,faceInfoArrayFieldID);
    env->SetIntField(faceInfoArrayObject,faceInfoArrayFieldID.size,faceInfoArray.size);
    env->SetObjectField(faceInfoArrayObject,faceInfoArrayFieldID.faceInfos,faceInfoArrayObjects);
    return faceInfoArrayObject;
}

jobject JNIHelper::toPointFloatArrayObject(JNIEnv *env, PointFloatArray pointFloatArray) {
    PointFloatFieldID pointFloatFieldID=getPointFloatFieldID(env);
    jobjectArray  pointFloatArrayObjects=newObjectArray(env,pointFloatFieldID,pointFloatArray.size);
    for(int i=0;i<pointFloatArray.size;i++){
        PointFloat pointFloat=pointFloatArray.data[i];
        jobject  pointFloatObject=newObject(env,pointFloatFieldID);
        env->SetDoubleField(pointFloatObject,pointFloatFieldID.x,pointFloat.x);
        env->SetDoubleField(pointFloatObject,pointFloatFieldID.y,pointFloat.y);
        env->SetObjectArrayElement(pointFloatArrayObjects,i,pointFloatObject);
        env->DeleteLocalRef(pointFloatObject);
    }
    PointFloatArrayFieldID  pointFloatArrayFieldID= getPointFloatArrayFieldID(env);
    jobject  pointFloatArrayObject=newObject(env,pointFloatArrayFieldID);
    env->SetObjectField(pointFloatArrayObject,pointFloatArrayFieldID.pointFloats,pointFloatArrayObjects);
    env->SetIntField(pointFloatArrayObject,pointFloatArrayFieldID.size,pointFloatArray.size);
    return pointFloatArrayObject;
}

jobject JNIHelper::toImageDataObject(JNIEnv *env, ImageData imageData) {
    auto *jByteData = (jbyte*)imageData.data;
    int size=imageData.width*imageData.height*imageData.channels;

    jbyteArray jByteDataObject=env->NewByteArray(size);
    env->SetByteArrayRegion(jByteDataObject, 0, size, jByteData);

    ImageDataFieldID imageDataFieldID=getImageDataFieldID(env);
    jobject imageDataObject= newObject(env,imageDataFieldID);
    env->SetObjectField(imageDataObject,imageDataFieldID.data,jByteDataObject);
    env->SetIntField(imageDataObject,imageDataFieldID.width,imageData.width);
    env->SetIntField(imageDataObject,imageDataFieldID.height,imageData.height);
    env->SetIntField(imageDataObject,imageDataFieldID.channels,imageData.channels);
    env->DeleteLocalRef(jByteDataObject);
    free(imageData.data);
    return imageDataObject;
}

jobject JNIHelper::toQueryResultObject(JNIEnv *env, QueryResult queryResult) {
    QueryResultFieldID queryResultFieldID=getQueryResultFieldID(env);
    jobject queryResultObject= newObject(env,queryResultFieldID);
    env->SetIntField(queryResultObject,queryResultFieldID.index,queryResult.index);
    env->SetFloatField(queryResultObject,queryResultFieldID.score,queryResult.score);
    return queryResultObject;
}

jobject JNIHelper::toQueryResultArrayObject(JNIEnv *env, QueryResultArray queryResultArray) {
    QueryResultFieldID queryResultFieldID=getQueryResultFieldID(env);
    jobjectArray  queryResultArrayObjects=newObjectArray(env,queryResultFieldID,queryResultArray.size);
    for (int i=0;i<queryResultArray.size;i++){
        QueryResult queryResult=queryResultArray.data[i];
        jobject queryResultObject= toQueryResultObject(env,queryResult);
        env->SetObjectArrayElement(queryResultArrayObjects,i,queryResultObject);
        env->DeleteLocalRef(queryResultObject);
    }
    QueryResultArrayFieldID queryResultArrayFieldID=getQueryResultArrayFieldID(env);
    jobject queryResultArrayObject=newObject(env,queryResultArrayFieldID);
    env->SetIntField(queryResultArrayObject,queryResultArrayFieldID.size,queryResultArray.size);
    env->SetObjectField(queryResultArrayObject,queryResultArrayFieldID.queryResults,queryResultArrayObjects);
    return queryResultArrayObject;
}

jobject JNIHelper::toFaceDataBaseDataObject(JNIEnv *env, FaceDataBaseData faceDataBaseData) {
    auto *jByteData = (jbyte*)faceDataBaseData.data;
    int size=faceDataBaseData.size;
    jbyteArray jByteDataObject=env->NewByteArray(size);
    env->SetByteArrayRegion(jByteDataObject, 0, size, jByteData);
    FaceDataBaseDataFieldID faceDataBaseDataFieldID=getFaceDataBaseDataFieldID(env);
    jobject faceDataBaseDataObject= newObject(env,faceDataBaseDataFieldID);
    env->SetIntField(faceDataBaseDataObject,faceDataBaseDataFieldID.size,size);
    env->SetObjectField(faceDataBaseDataObject,faceDataBaseDataFieldID.data,jByteDataObject);
    env->DeleteLocalRef(jByteDataObject);
    free(faceDataBaseData.data);
    return faceDataBaseDataObject;
}

jobjectArray JNIHelper::newObjectArray(JNIEnv *env, JClassDef classDef, int length) {
    jclass clazz = env->FindClass(classDef.className);
    return env->NewObjectArray(length, clazz, nullptr);
}



























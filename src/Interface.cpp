

#include <in_bugr_jni_FaceEngine.h>
#include <string>
#include <iostream>
#include <FaceEngine.h>
#include <JNIHelper.h>
sf2cs::FaceEngine * engine= nullptr;
const std::string FD_MODEL= "/fd_2_00.dat"; //NOLINT
const std::string  PD_MODEL_5="/pd_2_00_pts5.dat";//NOLINT
const std::string  PD_MODEL_81="/pd_2_00_pts81.dat";//NOLINT
const std::string FR_MODEL="/fr_2_10.dat";//NOLINT
using namespace sf2cs;
JNIEXPORT jboolean JNICALL Java_in_bugr_jni_FaceEngine_init
(JNIEnv *env, jobject obj, jstring model_dir,jint device,jint id) {

    //如果已初始化则直接返回
    if (engine!= nullptr) {
        return true;
    }
    if (NULL == model_dir) {
        return false;
    }
    std::string dir = env->GetStringUTFChars(model_dir, 0);
    if (dir.empty()) {
        return false;
    }
    //初始化model
    seeta::ModelSetting FDModel( dir+FD_MODEL, seeta::ModelSetting::Device(device), id );
    seeta::ModelSetting PDModel( dir+PD_MODEL_5, seeta::ModelSetting::Device(device), id );
    seeta::ModelSetting FRModel( dir+FR_MODEL, seeta::ModelSetting::Device(device), id );
    engine= new sf2cs::FaceEngine(FDModel, PDModel, FRModel);
    env->DeleteLocalRef(model_dir);
    return true;
}



JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_detectFace
(JNIEnv *env, jobject obj, jobject imgDataObject){
    ImageData   imageData= JNIHelper::toImageData(env,imgDataObject);
    FaceInfoArray faceInfoArray= engine->detectFace(imageData);
    env->DeleteLocalRef(imgDataObject);
    return JNIHelper::toFaceInfoArrayObject(env,faceInfoArray);
}


JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_detectPoints
(JNIEnv *env, jobject obj, jobject imgDataObject, jobject rectObject){
    ImageData imageData= JNIHelper::toImageData(env,imgDataObject);
    Rect rect= JNIHelper::toRect(env,rectObject);
    PointFloatArray pointFloatArray=engine->detectPoints(imageData,rect);

    env->DeleteLocalRef(imgDataObject);
    env->DeleteLocalRef(rectObject);
    return JNIHelper::toPointFloatArrayObject(env,pointFloatArray);
}

JNIEXPORT jfloat JNICALL Java_in_bugr_jni_FaceEngine_compare
        (JNIEnv * env, jobject obj,jobject imgDataObject1, jobject rectObject1, jobject imgDataObject2, jobject rectObject2){
    ImageData imageData1=JNIHelper::toImageData(env,imgDataObject1);
    ImageData imageData2=JNIHelper::toImageData(env,imgDataObject2);
    Rect rect1=JNIHelper::toRect(env,rectObject1);
    Rect rect2=JNIHelper::toRect(env,rectObject2);
    env->DeleteLocalRef(imgDataObject1);
    env->DeleteLocalRef(imgDataObject2);
    env->DeleteLocalRef(rectObject1);
    env->DeleteLocalRef(rectObject2);
    return engine->compare(imageData1,rect1,imageData2,rect2);
}

JNIEXPORT jfloat JNICALL Java_in_bugr_jni_FaceEngine_compareByCroppedFace
        (JNIEnv * env , jobject obj , jobject imgDataObject1, jobject imgDataObject2){
    ImageData imageData1=JNIHelper::toImageData(env,imgDataObject1);
    ImageData imageData2=JNIHelper::toImageData(env,imgDataObject2);
    env->DeleteLocalRef(imgDataObject1);
    env->DeleteLocalRef(imgDataObject2);
    return engine->compareByCroppedFace(imageData1,imageData2);
}


JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_crop
        (JNIEnv * env , jobject obj, jobject imgDataObject,jobject pointFloatArrayObject){
    ImageData imageData= JNIHelper::toImageData(env,imgDataObject);
    PointFloatArray pointFloatArray=JNIHelper::toPointFloatArray(env,pointFloatArrayObject);
    auto resultImageData= engine->crop(imageData,pointFloatArray.data);
    env->DeleteLocalRef(imgDataObject);
    env->DeleteLocalRef(pointFloatArrayObject);
    return JNIHelper::toImageDataObject(env,resultImageData);
}

JNIEXPORT jint JNICALL Java_in_bugr_jni_FaceEngine_registerByCroppedFace
        (JNIEnv * env, jobject obj, jobject faceImageDataObject){
    ImageData imageData=JNIHelper::toImageData(env,faceImageDataObject);
    env->DeleteLocalRef(faceImageDataObject);
    return engine->registerByCroppedFace(imageData);
}

JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_queryByCroppedFace
        (JNIEnv * env , jobject obj , jobject faceImageDataObject){
    ImageData imageData=JNIHelper::toImageData(env,faceImageDataObject);
    QueryResult queryResult= engine->queryByCroppedFace(imageData);
    env->DeleteLocalRef(faceImageDataObject);
    return JNIHelper::toQueryResultObject(env,queryResult);
}

JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_queryTopByCroppedFace
        (JNIEnv * env , jobject obj, jobject faceImageDataObject, jint n){
    ImageData imageData=JNIHelper::toImageData(env,faceImageDataObject);
    QueryResultArray queryResultArray= engine->queryTopByCroppedFace(imageData,n);
    env->DeleteLocalRef(faceImageDataObject);
    return JNIHelper::toQueryResultArrayObject(env,queryResultArray);
}

JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_queryAboveByCroppedFace
        (JNIEnv *env , jobject obj , jobject faceImageDataObject, jfloat threshold, jint n){
    ImageData imageData=JNIHelper::toImageData(env,faceImageDataObject);
    QueryResultArray queryResultArray= engine->queryAboveByCroppedFace(imageData,threshold,n);
    env->DeleteLocalRef(faceImageDataObject);
    return JNIHelper::toQueryResultArrayObject(env,queryResultArray);
}

JNIEXPORT jint JNICALL Java_in_bugr_jni_FaceEngine_count
        (JNIEnv * env , jobject obj){
    return engine->count();
}
JNIEXPORT void JNICALL Java_in_bugr_jni_FaceEngine_clear
        (JNIEnv * env , jobject obj){
    engine->clear();
}
JNIEXPORT jobject JNICALL Java_in_bugr_jni_FaceEngine_save
        (JNIEnv * env, jobject obj){
    FaceDataBaseData faceDataBaseData= engine->save();
    return  JNIHelper::toFaceDataBaseDataObject(env,faceDataBaseData);
}

JNIEXPORT jboolean JNICALL Java_in_bugr_jni_FaceEngine_load
        (JNIEnv * env, jobject obj, jobject faceDataBaseDataObject){
    FaceDataBaseData faceDataBaseData=JNIHelper::toFaceDataBaseData(env,faceDataBaseDataObject);
    return engine->load(faceDataBaseData);
}



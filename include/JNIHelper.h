#include <seeta/CStruct.h>
#include <jni.h>
#include "CJFieldStruct.h"
#include "SF2CSStruct.h"

class JNIHelper
{
public:
    JNIHelper();
    ~JNIHelper();

    //将java的SeetaImageData对象转成C++的SeetaImageData
    static ImageData toImageData(JNIEnv *env, jobject jImg);

    static Rect toRect(JNIEnv * env,jobject rectObject);

    static PointFloatArray toPointFloatArray(JNIEnv * env,jobject pointFloatArrayObject);

    static FaceDataBaseData toFaceDataBaseData(JNIEnv * env,jobject faceDataBaseDataObject);

    /////////////////////////

    static jobject toFaceInfoObject(JNIEnv *env,FaceInfoArray faceInfoArray,int index);

    static jobject toFaceInfoArrayObject(JNIEnv *env, FaceInfoArray faceInfoArray);

    static jobject toPointFloatArrayObject(JNIEnv * env,PointFloatArray pointFloatArray);

    static jobject toImageDataObject(JNIEnv * env,ImageData imageData);

    static jobject toQueryResultObject(JNIEnv * env,QueryResult queryResult);

    static jobject  toQueryResultArrayObject(JNIEnv * env,QueryResultArray queryResultArray);

    static jobject  toFaceDataBaseDataObject(JNIEnv * env,FaceDataBaseData faceDataBaseData);

    /////////////////////////

    static ImageDataFieldID getImageDataFieldID(JNIEnv *env);

    static RectFieldID getRectFieldID(JNIEnv *env);

    static FaceInfoFieldID getFaceInfoFieldID(JNIEnv * env);

    static FaceInfoArrayFieldID getFaceInfoArrayFieldID(JNIEnv *env);

    static PointFloatArrayFieldID getPointFloatArrayFieldID(JNIEnv *env);

    static PointFloatFieldID getPointFloatFieldID(JNIEnv *env);

    static QueryResultFieldID getQueryResultFieldID(JNIEnv * env);

    static QueryResultArrayFieldID getQueryResultArrayFieldID(JNIEnv * env);

    static FaceDataBaseDataFieldID getFaceDataBaseDataFieldID(JNIEnv * env);

    ///////////////////////


    //创建对象
    static jobject newObject(JNIEnv *env, JClassDef classDef);

    //创建对象数组
    static jobjectArray  newObjectArray(JNIEnv *env, JClassDef classDef,int length);
};

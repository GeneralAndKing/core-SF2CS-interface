#ifndef INC_JFIELD_C_STRUCT_H
#define INC_JFIELD_C_STRUCT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

struct JClassDef
{
	char *className;
	jmethodID constructor;
	bool init;

	JClassDef(char *_className) {
		className = _className;
	}
};

struct ImageDataFieldID : JClassDef
{
	jfieldID data;
	jfieldID width;
	jfieldID height;
	jfieldID channels;

	ImageDataFieldID(char *_className):JClassDef(_className){}
};

struct RectFieldID : JClassDef
{
	jfieldID x;
	jfieldID y;
	jfieldID width;
	jfieldID height;
	RectFieldID(char *_className) :JClassDef(_className) {}
};

struct FaceInfoFieldID : JClassDef
{
    jfieldID rect;
    jfieldID score;
    FaceInfoFieldID(char *_className) :JClassDef(_className) {}
};

struct FaceInfoArrayFieldID : JClassDef
{
    jfieldID faceInfos;
    jfieldID size;
    FaceInfoArrayFieldID(char *_className) :JClassDef(_className) {}
};

struct PointFloatArrayFieldID:JClassDef{
    jfieldID pointFloats;
    jfieldID size;
    PointFloatArrayFieldID(char *_className) :JClassDef(_className) {}
};

struct PointFloatFieldID : JClassDef
{
	jfieldID x;
	jfieldID y;
	PointFloatFieldID(char *_className) : JClassDef(_className) {}
};

struct QueryResultFieldID : JClassDef
{
	jfieldID index;
	jfieldID score;
	QueryResultFieldID(char *_className) : JClassDef(_className) {}
};

struct QueryResultArrayFieldID:JClassDef{
    jfieldID queryResults;
    jfieldID size;
    QueryResultArrayFieldID(char *_className) : JClassDef(_className) {}
};

struct FaceDataBaseDataFieldID:JClassDef{
    jfieldID data;
    jfieldID size;
    FaceDataBaseDataFieldID(char *_className) : JClassDef(_className) {}
};
#ifdef __cplusplus
}
#endif
#endif

//
// Created by Dean Guo on 7/23/16.
//
#include "com_dean_testndk_JNIHelper.h"
#include "string.h"
#include "iostream"
#include "vector"
#include "algorithm"
#include <android/log.h>

using namespace std;
// Android log function wrappers
static const char* kTAG = "testNDK";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

struct GLOBAL_CONTEXT {
    JavaVM* javaVM;
    jclass mainActivityClz;
    jobject mainActivityObj;

    jclass jniHelperClz;
    jobject jniHelperObj;
};

GLOBAL_CONTEXT mContext;

void sendJavaMsg(JNIEnv *env, jobject instance, jmethodID func, const char *msg) {

    jstring javaMsg = env->NewStringUTF(msg);
    env->CallVoidMethod(instance, func, javaMsg);
//
//    jthrowable ex = env->ExceptionOccurred();
//    if (0 != ex) {
//        env->ExceptionClear();
//        LOGE("Exception-sendJavaMsg!");
//    }
//    env->DeleteLocalRef(javaMsg);
}

void callSetResult(JNIEnv *env, vector<int> vector_) {

    char buff[1000] = "";

    vector<int>::iterator it;

    for (it = vector_.begin(); it != vector_.end(); it++) {
        char numChar[100] = "";
        sprintf(numChar, "%d", *it);
        strcat(numChar, ",");
        strcat(buff, numChar);
    }

    jstring javaMsg = env->NewStringUTF(buff);
    jthrowable ex = env->ExceptionOccurred();
    if (0 != ex) {
        env->ExceptionClear();
        env->DeleteLocalRef(javaMsg);
        LOGE("Exception-sendJavaMsg!");
    } else {
        jmethodID methodID = env->GetMethodID(mContext.mainActivityClz, "setResultText", "(Ljava/lang/String;)V");
        env->CallVoidMethod(mContext.mainActivityObj, methodID, javaMsg);
        env->DeleteLocalRef(javaMsg);
    }
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {

    LOGI("JNI_OnLoad");

    JNIEnv* env;

    mContext.javaVM = vm;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("JNI_ERR");
        return JNI_ERR; // 不支持该版本
    }

    jclass clz = env->FindClass("com/dean/testndk/JNIHelper");
    mContext.jniHelperClz = (jclass) env->NewGlobalRef(clz);

    jmethodID jniHelperCtor = env->GetMethodID(mContext.jniHelperClz, "<init>", "()V");
    jobject handler = env->NewObject(mContext.jniHelperClz, jniHelperCtor);
    mContext.jniHelperObj = env->NewGlobalRef(handler);

    jmethodID statusId = env->GetMethodID(mContext.jniHelperClz, "updateStatus", "(Ljava/lang/String;)V");
    sendJavaMsg(env, mContext.jniHelperObj, statusId, "JNI: initializing...");

    return JNI_VERSION_1_6;
}

JNIEXPORT jstring JNICALL Java_com_dean_testndk_JNIHelper_getStringFromNative
        (JNIEnv *env, jclass jclz) {
    return env->NewStringUTF("from Native");
}


JNIEXPORT jintArray JNICALL
Java_com_dean_testndk_MainActivity_doSort(JNIEnv *env, jobject instance, jintArray arr_) {
    mContext.mainActivityClz = env->GetObjectClass(instance);
    mContext.mainActivityObj = env->NewGlobalRef(instance);

    // 获取传递过来的数组指针
    jint *nums = env->GetIntArrayElements(arr_, NULL);
    // 获取数组长度
    jsize len = env->GetArrayLength(arr_);

    // 排序后需要返回的数组
    jintArray array = env->NewIntArray(len);

    // 使用标准库中的vector排序
    vector<int> mVector;
    for (int i=0; i< len; i++) {
        mVector.push_back(nums[i]);
    }
    sort(mVector.begin(), mVector.end());

    callSetResult(env, mVector);

    env->ReleaseIntArrayElements(arr_, nums, 0);
}

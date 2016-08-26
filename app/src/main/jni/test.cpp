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

/**
 * 全局引用
 */
GLOBAL_CONTEXT mContext;

void sendJavaMsg(JNIEnv *env, jobject instance, jmethodID func, const char *msg) {

    jstring javaMsg = env->NewStringUTF(msg);
    env->CallVoidMethod(instance, func, javaMsg);
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

/**
 * 根据排序好的vector集合, 创建排序数组返回
 */
void callSetArrayResult(JNIEnv *env, vector<int> vector_) {

    int size = vector_.size();

    // 排序后需要返回的数组
    jintArray array = env->NewIntArray(size);

    // 为jni数组赋值
    jint *num = new jint[size];
    for (int i = 0; i < size; i++)
    {
        num[i] = vector_[i];
    }
    env->SetIntArrayRegion(array, 0, size, num);

    // 调用java方法传递排序好的数组
    jmethodID methodID = env->GetMethodID(mContext.mainActivityClz, "setResultText", "([I)V");
    env->CallVoidMethod(mContext.mainActivityObj, methodID, array);

    // 释放数组
    env->ReleaseIntArrayElements(array, num, 0);
}

/**
 * 系统函数, JNI初始化时调用。
 * 可在这个函数这里做一些初始化赋值
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {

    LOGI("JNI_OnLoad");

    JNIEnv* env;

    mContext.javaVM = vm;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("JNI_ERR");
        return JNI_ERR; // 不支持该版本
    }

    // 对JNIHelper设置全局引用
    jclass clz = env->FindClass("com/dean/testndk/JNIHelper");
    mContext.jniHelperClz = (jclass) env->NewGlobalRef(clz);

    jmethodID jniHelperCtor = env->GetMethodID(mContext.jniHelperClz, "<init>", "()V");
    jobject handler = env->NewObject(mContext.jniHelperClz, jniHelperCtor);
    mContext.jniHelperObj = env->NewGlobalRef(handler);

    // 调用JNIHelper中updateStatus方法打印信息
    jmethodID statusId = env->GetMethodID(mContext.jniHelperClz, "updateStatus", "(Ljava/lang/String;)V");
    sendJavaMsg(env, mContext.jniHelperObj, statusId, "JNI: initializing...");

    return JNI_VERSION_1_6;
}

/**
 * 简单返回一个字符串
 */
JNIEXPORT jstring JNICALL Java_com_dean_testndk_JNIHelper_getStringFromNative
        (JNIEnv *env, jclass jclz) {
    return env->NewStringUTF("from Native");
}

/**
 * 排序方法, 成功返回true, 否则false
 */
JNIEXPORT jboolean JNICALL
Java_com_dean_testndk_MainActivity_doSort(JNIEnv *env, jobject instance, jintArray arr_) {
    // 设置全局引用
    mContext.mainActivityClz = env->GetObjectClass(instance);
    mContext.mainActivityObj = env->NewGlobalRef(instance);

    // 获取传递过来的数组指针
    jint *nums = env->GetIntArrayElements(arr_, NULL);
    // 获取数组长度
    jsize len = env->GetArrayLength(arr_);

    // 使用标准库中的vector排序
    vector<int> mVector;
    for (int i=0; i< len; i++) {
        mVector.push_back(nums[i]);
    }
    sort(mVector.begin(), mVector.end());

    // 调用返回结果函数
    callSetArrayResult(env, mVector);

    // 释放数组
    env->ReleaseIntArrayElements(arr_, nums, 0);

    // 判断是否有异常, 没有表示成功返回true, 否则false
    jthrowable ex = env->ExceptionOccurred();
    if (0 != ex) {
        env->ExceptionClear();
        LOGE("Exception!");
        return false;
    } else {
        return true;
    }
}

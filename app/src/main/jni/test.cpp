//
// Created by Dean Guo on 8/2/16.
//

#include "com_dean_testndk_JNIHelper.h"
#include <android/log.h>
#include <string.h>

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
    jobject mainAcitivtyObj;

    jclass jniHelperClz;
    jobject jniHelperObj;
};

GLOBAL_CONTEXT mContext;

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

    return JNI_VERSION_1_6;
}



JNIEXPORT jintArray JNICALL
Java_com_dean_testndk_JNIHelper_doOrder(JNIEnv *env, jclass type, jintArray nums_) {
    jint *nums = env->GetIntArrayElements(nums_, NULL);

    jsize len = env->GetArrayLength(nums_);
        //打印数组中的值

    for (int i=0; i<len; i++) {
        LOGI("asdfasf %d", nums[i]);
    }

    // TODO

    env->ReleaseIntArrayElements(nums_, nums, 0);
}
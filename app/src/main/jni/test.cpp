//
// Created by Dean Guo on 7/23/16.
//
#include "com_dean_testndk_JNIHelper.h"

struct GLOBAL_INSTANCE {
    jclass mainActivityClz;
    jobject mainActivityObj;
    jclass jniHelperClz;
    jobject jniHelperObj;
};

GLOBAL_INSTANCE mGlobalInstance;

void sendJavaMsg(JNIEnv *env, jobject instance, jmethodID func, const char *msg) {
    jstring javaMsg = env->NewStringUTF(msg);
    env->CallVoidMethod(instance, func, javaMsg);
    env->DeleteLocalRef(javaMsg);
}

JNIEXPORT jstring JNICALL Java_com_dean_testndk_JNIHelper_getStringFromNative
        (JNIEnv *env, jclass jclass1) {
    return env->NewStringUTF("haha");
}

JNIEXPORT void JNICALL
Java_com_dean_testndk_MainActivity_doCalcPlus(JNIEnv *env, jobject instance) {

    mGlobalInstance.mainActivityClz = env->GetObjectClass(instance);
    mGlobalInstance.mainActivityObj = env->NewGlobalRef(instance);

    mGlobalInstance.jniHelperClz = env->FindClass("com/dean/testndk/JNIHelper");

    jmethodID jniHelperCtor = env->GetMethodID(mGlobalInstance.jniHelperClz, "<init>", "()V");
    jobject handler = env->NewObject(mGlobalInstance.jniHelperClz, jniHelperCtor);
    mGlobalInstance.jniHelperObj = env->NewGlobalRef(handler);

    jmethodID statusId = env->GetMethodID(mGlobalInstance.jniHelperClz, "updateStatus", "(Ljava/lang/String;)V");
    sendJavaMsg(env, mGlobalInstance.jniHelperObj, statusId, "TickerThread status: initializing...");

    // get number1

    // get number2

}

void nativeCallJavaClass(JNIEnv *env, jobject instance) {

    jclass clazz = env->GetObjectClass(instance);

    // 获取实例域的FieldID
    jfieldID instanceFieldId = env->GetFieldID(clazz, "instanceField", "Ljava/lang/String;");
    // 获取实例域
    jstring instanceField = (jstring) env->GetObjectField(instance, instanceFieldId);

    // 获取实例方法的MethodID
    jmethodID instanceMethodId = env->GetMethodID(clazz, "staticMethod", "Ljava/lang/String;");
    jstring  instanceMethod = (jstring) env->CallObjectMethod(clazz, instanceMethodId);


//    jclass globalClazz;
//    jclass localClazz = env->FindClass("java/lang/String");
//    globalClazz = (jclass) env->NewGlobalRef(localClazz);
//    env->DeleteGlobalRef(globalClazz);

    jclass weakGlobalClazz;
    jclass localClazz = env->FindClass("java/lang/String");
    weakGlobalClazz = (jclass) env->NewWeakGlobalRef(localClazz);
    env->DeleteGlobalRef(weakGlobalClazz);

    if (JNI_FALSE == env->IsSameObject(weakGlobalClazz, nullptr)) {
        // 有效
    } else {
        // 对象被垃圾回收器回收, 不可使用
    }
};
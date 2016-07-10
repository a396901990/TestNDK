#include "com_dean_testndk_JNIHelper.h"

JNIEXPORT jstring JNICALL Java_com_dean_testndk_JNIHelper_getStringFromNative
  (JNIEnv * env, jobject jclass) {
    return (*env)->NewStringUTF(env, "return from native c");
  }

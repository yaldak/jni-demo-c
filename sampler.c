#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "gldemo.h"
#include "mpdemo.h"
#include "strdemo.h"

#include "cc_kako_examples_jni_NativeSampler.h"

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativePrint
(JNIEnv *env, jobject obj) {
    printf("\nHello World from C\n");
}

JNIEXPORT jstring JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeString
(JNIEnv *env, jclass clazz) {
    char text[60] = "Hello from C";

    jstring result = (*env)->NewStringUTF(env, text);

    return result;
}

JNIEXPORT jint JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeInt
(JNIEnv *env, jclass clazz) {
    int value = 1337;

    /* Just return the value directly */
    return value;
}

JNIEXPORT jintArray JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeIntArray
(JNIEnv *env, jclass clazz) {
    int size = 10;

    jintArray result = (*env)->NewIntArray(env, size);
    if (NULL == result) {
        /* out of memory error thrown */
        return NULL;
    }

    // fill a temp structure to use to populate the java int array
    jint fill[size];
    for (int i = 0; i < size; i++) {
        // put whatever logic you want to populate the values here.
        fill[i] = i;
    }

    // move from the temp structure to the java structure
    (*env)->SetIntArrayRegion(env, result, 0, size, fill);
    return result;
}

JNIEXPORT jobject JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeIntegerObject
(JNIEnv *env, jclass clazz) {
    int number = 10;

    jclass cls = (*env)->FindClass(env, "java/lang/Integer");
    jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");

    if (NULL == midInit) {
        return NULL;
    }

    jobject newObj = (*env)->NewObject(env, cls, midInit, number);

    return newObj;
}

JNIEXPORT jstring JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeRotateString
  (JNIEnv *env, jclass clazz, jstring input) {
    const char *inputstr = (*env)->GetStringUTFChars(env, input, NULL);
    
    if (NULL == inputstr) {
        return NULL;
    }
    
    char* transformed = (char*) inputstr;
    
    strrev(transformed);

    jstring result = (*env)->NewStringUTF(env, transformed);
    
    // Free transformed? inputstr?

    return result;
}

JNIEXPORT jint JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeArraySumParallel
  (JNIEnv *env, jclass clazz, jintArray values) {
    return 55;
}

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeOpenGLTriangle
  (JNIEnv *env, jclass clazz) {
    gldemo_run();
}

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeRaiseException
  (JNIEnv *env, jclass clazz) {
    jclass Exception = (*env)->FindClass(env, "java/lang/Exception");
    (*env)->ThrowNew(env, Exception, "Exception from C.");
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <jni.h>
#include <stdio.h>
#include "cc_kako_examples_jni_NativeSampler.h"

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativePrint
        (JNIEnv *env, jobject obj)
{

    printf("\nHello World from C\n");

}

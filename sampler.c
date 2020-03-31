#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h> 

#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>   // freeglut.h might be a better alternative, if available.
#endif

#include "cc_kako_examples_jni_NativeSampler.h"

#define MAX_THREAD 4

void display() { // Display function will draw the image.
    glClearColor(0, 0, 0, 1); // (In fact, this is the default.)
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); // red
    glVertex2f(-0.8, -0.8);
    glColor3f(0, 1, 0); // green
    glVertex2f(0.8, -0.8);
    glColor3f(0, 0, 1); // blue
    glVertex2f(0, 0.9);
    glEnd();

    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

void runGlTest() { // Initialize GLUT and 
    int argc = 1;
    char *argv[1] = {" "};

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE); // Use single color buffer and no depth buffer.
    glutInitWindowSize(500, 500); // Size of display area, in pixels.
    glutInitWindowPosition(100, 100); // Location of window in screen coordinates.
    glutCreateWindow("GL RGB Triangle"); // Parameter is window title.
    glutDisplayFunc(display); // Called when the window needs to be redrawn.

    glutMainLoop(); // Run the event loop!  This function does not return.
    // Program ends when user closes the window.
    //return 0;
}

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativePrint
(JNIEnv *env, jobject obj) {
    runGlTest();
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
    char text[60] = "tset";

    jstring result = (*env)->NewStringUTF(env, text);

    return result;

    // const char *name = (*env)->GetStringUTFChars(env, string, NULL);
    // (*env)->ReleaseStringUTFChars(env,string, name);    
}

JNIEXPORT jint JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeArraySumParallel
  (JNIEnv *env, jclass clazz, jintArray values) {
    return 55;
}

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeOpenGLTriangle
  (JNIEnv *env, jclass clazz) {
    runGlTest();
}

JNIEXPORT void JNICALL Java_cc_kako_examples_jni_NativeSampler_nativeRaiseException
  (JNIEnv *env, jclass clazz) {
    jclass Exception = (*env)->FindClass(env, "java/lang/Exception");
    (*env)->ThrowNew(env, Exception, "Exception from C.");
}

char *strrev(char *str) {
    if (!str || ! *str) {
        return str;
    }

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

void* sum_array(void* arg) 
{ 
  
    // Each thread computes sum of 1/4th of array 
    int thread_part = part++; 
  
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++) 
        sum[thread_part] += a[i]; 
} 

int sum_array_parallel() 
{ 
  
    pthread_t threads[MAX_THREAD]; 
  
    // Creating 4 threads 
    for (int i = 0; i < MAX_THREAD; i++) 
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL); 
  
    // joining 4 threads i.e. waiting for all 4 threads to complete 
    for (int i = 0; i < MAX_THREAD; i++) 
        pthread_join(threads[i], NULL); 
  
    // adding sum of all 4 parts 
    int total_sum = 0; 
    for (int i = 0; i < MAX_THREAD; i++) 
        total_sum += sum[i]; 
  
    return total_sum;
} 
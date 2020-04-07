/*
 * The MIT License
 *
 * Copyright 2020 yalda.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <pthread.h>

#define MAX 16
#define MAX_THREAD 4

int a[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
int sum[4] = { 0 };
int part = 0;

void* sum_array(void* arg) {
    // Each thread computes sum of 1/4th of array 
    int thread_part = part++;
  
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++) 
        sum[thread_part] += a[i];
}

int sum_array_parallel(int arr[], int threadCount) {
    pthread_t threads[MAX_THREAD];
  
    // Creating 4 threads 
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, sum_array, (void*) NULL);
    }
  
    // joining 4 threads i.e. waiting for all 4 threads to complete 
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL); 
    }
  
    // adding sum of all 4 parts 
    int total_sum = 0; 
    for (int i = 0; i < MAX_THREAD; i++) {
        total_sum += sum[i]; 
    }
  
    return total_sum;
}

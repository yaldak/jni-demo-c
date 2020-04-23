#include <pthread.h>

#define MAX_THREAD 4

int parts[4] = { 0 };
int part = 0;

void* sum_array_internal(void* arg) {
    int* arr = (int*) arg;
    int max = 16;
    
    // Each thread computes sum of 1/4th of array 
    int thread_part = part++;
  
    for (int i = thread_part * (max / 4); i < (thread_part + 1) * (max / 4); i++) {
        parts[thread_part] += arr[i];
    }
    
    pthread_exit(0);
}

int sum_array_parallel(int arr[]) {
    pthread_t threads[MAX_THREAD];
  
    /* Create threads */
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_create(&threads[i], NULL, sum_array_internal, (void*) arr);
    }
  
    /* Join threads (blocking) */
    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL); 
    }
  
    /* Reduce the total sum */ 
    int total = 0; 
    for (int i = 0; i < MAX_THREAD; i++) {
        total += parts[i]; 
    }
    
    parts = { 0 };
    part = 0;
  
    return total;
}

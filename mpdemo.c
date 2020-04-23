#include <pthread.h>

#define MAX 16
#define THREAD_COUNT 4

int a[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
int parts[4] = { 0 };
int part = 0;

void* sum_array_internal(void* arg) {
    int thread_part = part++;
  
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++) {
        parts[thread_part] += a[i];
    }
}

int sum_array_parallel() {
    pthread_t threads[THREAD_COUNT];
  
    /* Create threads */
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, sum_array_internal, (void*) NULL);
    }
  
    /* Join threads (blocking) */
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL); 
    }
  
    /* Reduce the total sum */ 
    int total = 0; 
    for (int i = 0; i < THREAD_COUNT; i++) {
        total += parts[i]; 
    }
  
    return total;
}

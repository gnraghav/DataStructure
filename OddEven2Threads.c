#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 50

pthread_mutex_t mutex;
pthread_cond_t cond;
volatile int count = 0;

void* printEvenNum(void* arg) {
    while (count < MAX) {
        pthread_mutex_lock(&mutex);
        while (count % 2 != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("%d ", count++);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(0);
}

void* printOddNum(void* arg) {
    while (count < MAX) {
        pthread_mutex_lock(&mutex);
        while (count % 2 != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("%d ", count++);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(0);
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&thread1, NULL, printEvenNum, NULL);
    pthread_create(&thread2, NULL, printOddNum, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

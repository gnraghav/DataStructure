#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to hold synchronization variables and n
typedef struct {
    int n; // The number of pairs to print
    pthread_mutex_t mt; // Mutex for synchronization
    pthread_cond_t c1, c2, c3; // Condition variables for zero, odd, and even
    int num; // Current number to print (0, 1, 2, ...)
    int turn; // 0: zero's turn, 1: odd's turn, 2: even's turn
} ZeroEvenOdd;

// Create the ZeroEvenOdd object
ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n; // Set the total number of pairs
    obj->num = 1; // Start with the first number (1)
    obj->turn = 0; // Start with zero's turn
    pthread_mutex_init(&obj->mt, NULL);
    pthread_cond_init(&obj->c1, NULL); // Condition variable for zero
    pthread_cond_init(&obj->c2, NULL); // Condition variable for odd
    pthread_cond_init(&obj->c3, NULL); // Condition variable for even
    return obj;
}

// Function to print a number
void printNumber(int x) {
    printf("%d", x);
}

// Thread function for printing zero
void* zero(void* param) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)param;
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->mt);
        while (obj->turn != 0) {
            pthread_cond_wait(&obj->c1, &obj->mt);
        }
        printNumber(0); // Print 0
        // Determine whose turn it is next (odd or even)
        obj->turn = (i % 2 == 0) ? 1 : 2; // Alternate between odd and even
        if (obj->turn == 1) {
            pthread_cond_signal(&obj->c2); // Signal odd thread
        } else {
            pthread_cond_signal(&obj->c3); // Signal even thread
        }
        pthread_mutex_unlock(&obj->mt);
    }
    return NULL;
}

// Thread function for printing odd numbers
void* odd(void* param) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)param;
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mt);
        while (obj->turn != 1) {
            pthread_cond_wait(&obj->c2, &obj->mt);
        }
        printNumber(i); // Print the current odd number
        obj->turn = 0; // Set turn back to zero
        pthread_cond_signal(&obj->c1); // Signal zero thread
        pthread_mutex_unlock(&obj->mt);
    }
    return NULL;
}

// Thread function for printing even numbers
void* even(void* param) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*)param;
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&obj->mt);
        while (obj->turn != 2) {
            pthread_cond_wait(&obj->c3, &obj->mt);
        }
        printNumber(i); // Print the current even number
        obj->turn = 0; // Set turn back to zero
        pthread_cond_signal(&obj->c1); // Signal zero thread
        pthread_mutex_unlock(&obj->mt);
    }
    return NULL;
}

// Clean up the ZeroEvenOdd object
void zeroEvenOddFree(ZeroEvenOdd* obj) {
    pthread_mutex_destroy(&obj->mt);
    pthread_cond_destroy(&obj->c1);
    pthread_cond_destroy(&obj->c2);
    pthread_cond_destroy(&obj->c3);
}

int main() {
    int n = 5; // The number of pairs, resulting in "0102030405"
    ZeroEvenOdd* obj = zeroEvenOddCreate(n);
    
    pthread_t t1, t2, t3;
    
    // Create threads for zero, odd, and even
    pthread_create(&t1, NULL, zero, obj);
    pthread_create(&t2, NULL, odd, obj);
    pthread_create(&t3, NULL, even, obj);
    
    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    printf("\n"); // Add a newline after the final output
    
    // Free resources
    zeroEvenOddFree(obj);
    return 0;
}

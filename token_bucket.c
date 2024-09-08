#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUCKET_SIZE 10
#define TOKEN_RATE 1

typedef struct {
    int tokens;
    pthread_mutex_t lock;
} TokenBucket;

void* token_generator(void* arg) {
    TokenBucket* bucket = (TokenBucket*)arg;
    while (1) {
        pthread_mutex_lock(&bucket->lock);
        if (bucket->tokens < BUCKET_SIZE) {
            bucket->tokens++;
            printf("Token added. Current tokens: %d\n", bucket->tokens);
        }
        pthread_mutex_unlock(&bucket->lock);
        sleep(1); // Add a token every second
    }
    return NULL;
}

int consume_token(TokenBucket* bucket) {
    pthread_mutex_lock(&bucket->lock);
    if (bucket->tokens > 0) {
        bucket->tokens--;
        pthread_mutex_unlock(&bucket->lock);
        return 1; // Token consumed
    } else {
        pthread_mutex_unlock(&bucket->lock);
        return 0; // No tokens available
    }
}

int main() {
    TokenBucket bucket;
    bucket.tokens = 0;
    pthread_mutex_init(&bucket.lock, NULL);

    pthread_t token_thread;
    pthread_create(&token_thread, NULL, token_generator, &bucket);

    while (1) {
        if (consume_token(&bucket)) {
            printf("Packet sent.\n");
        } else {
            printf("No tokens available. Packet dropped.\n");
        }
        sleep(1); // Attempt to send a packet every second
    }

    pthread_join(token_thread, NULL);
    pthread_mutex_destroy(&bucket.lock);
    return 0;
}

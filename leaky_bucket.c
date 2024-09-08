#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUCKET_SIZE 10
#define OUTPUT_RATE 1

typedef struct {
    int size;
    int current_level;
} LeakyBucket;

void add_packet(LeakyBucket* bucket, int packet_size) {
    if (bucket->current_level + packet_size > bucket->size) {
        printf("Bucket overflow. Packet of size %d dropped.\n", packet_size);
    } else {
        bucket->current_level += packet_size;
        printf("Packet of size %d added. Current level: %d\n", packet_size, bucket->current_level);
    }
}

void leak(LeakyBucket* bucket) {
    if (bucket->current_level > 0) {
        bucket->current_level -= OUTPUT_RATE;
        if (bucket->current_level < 0) {
            bucket->current_level = 0;
        }
        printf("Leaked %d unit. Current level: %d\n", OUTPUT_RATE, bucket->current_level);
    } else {
        printf("Bucket is empty. Nothing to leak.\n");
    }
}

int main() {
    LeakyBucket bucket;
    bucket.size = BUCKET_SIZE;
    bucket.current_level = 0;

    int packets[] = {4, 8, 1, 2, 6, 3};
    int num_packets = sizeof(packets) / sizeof(packets[0]);

    for (int i = 0; i < num_packets; i++) {
        add_packet(&bucket, packets[i]);
        sleep(1); // Simulate time delay between packet arrivals
        leak(&bucket);
    }

    return 0;
}

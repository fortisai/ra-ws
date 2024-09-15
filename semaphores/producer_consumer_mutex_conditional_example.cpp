#include <pthread.h>
#include <stdio.h>
#include "rfifo.h"
#include <stdlib.h>

#define FIFO_SIZE 10
#define QUEUE_SIZE 50

void *producer(void *arg) {
    rfifo_t *fifo = (rfifo_t *)arg;
    rfifo_packet_t *packet;
    packet = (rfifo_packet_t *)malloc(sizeof(rfifo_packet_t) + 1);
    for (int i = 0; i < QUEUE_SIZE; i++) {
        packet = (rfifo_packet_t *)malloc(sizeof(rfifo_packet_t) + 1);
        packet->type = i;
        packet->len = 1;
        packet->data[0] = i;
        rfifo_push(fifo, packet);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    rfifo_t *fifo = (rfifo_t *)arg;
    rfifo_packet_t *packet;
    while (1) {
        packet = rfifo_pop(fifo);
        if (packet == NULL) {
            pthread_exit(NULL);
        }
        printf("Received packet of type %d and length %d\n", packet->type, packet->len);
        free(packet);
    }
}

int main(int argc, char **argv) {
    rfifo_t *fifo;
    pthread_t prod, cons;
    fifo = rfifo_make(FIFO_SIZE);
    pthread_create(&prod, NULL, consumer, fifo);
    pthread_create(&cons, NULL, producer, fifo);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
}
#ifndef RFIFO_H
#define RFIFO_H

#include <stdint.h>
#include <cstdint>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    uint8_t type;
    uint8_t len;
    uint8_t data[0];
} rfifo_packet_t;

typedef struct{
    size_t size;
    size_t head;
    size_t tail;
    rfifo_packet_t **buffer;
    size_t elements;
    pthread_mutex_t lock;
    pthread_cond_t changed;
} rfifo_t;

rfifo_t *rfifo_make(size_t size) {
    rfifo_t *fifo = (rfifo_t *)malloc(sizeof(rfifo_t));
    fifo->size = size;
    fifo->head = 0;
    fifo->tail = 0;
    fifo->buffer = (rfifo_packet_t **)malloc(size * sizeof(rfifo_packet_t *));
    fifo->elements = 0;
    pthread_mutex_init(&(fifo->lock), NULL);
    pthread_cond_init(&(fifo->changed), NULL);
    return fifo;
}

int rfifo_push(rfifo_t *fifo, rfifo_packet_t *packet) {
    int status;
    pthread_mutex_lock(&fifo->lock);
    while (fifo->elements == fifo->size) {
        pthread_cond_wait(&(fifo->changed), &(fifo->lock));
    }
    printf("push, head: %d, tail: %d, elements: %d\n", (int)fifo->head, (int)fifo->tail, (int)fifo->elements);
    fifo->buffer[fifo->head] = packet;
    fifo->head = (fifo->head + 1) % fifo->size;
    status = ++(fifo->elements);
    pthread_cond_signal(&(fifo->changed));
    pthread_mutex_unlock(&(fifo->lock));
    return status;
}

rfifo_packet_t *rfifo_pop(rfifo_t *fifo) {
    rfifo_packet_t *packet;
    pthread_mutex_lock(&(fifo->lock));
    while (fifo->elements == 0) {
        pthread_cond_wait(&(fifo->changed), &(fifo->lock));
    }
    printf("pop, head: %d, tail: %d, elements: %d\n", (int)fifo->head, (int)fifo->tail, (int)fifo->elements);
    packet = fifo->buffer[fifo->tail];
    fifo->tail = (fifo->tail + 1) % fifo->size;
    fifo->elements--;
    pthread_cond_signal(&(fifo->changed));
    pthread_mutex_unlock(&(fifo->lock));
    return packet;
}

#endif // RFIFO_H

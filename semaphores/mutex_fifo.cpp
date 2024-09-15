int rfifo_push(rfifo_t *fifo, rfifo_packet_t *packet) {
    int status;
    pthread_mutex_lock(&(fifo->lock));
    while (fifo->elements == fifo->size);
    fifo->buffer[fifo->head] = packet;
    fifo->head = (fifo->head + 1) % fifo->size;
    status = ++(fifo->elements);
    pthread_mutex_unlock(&(fifo->lock));
    return status;
}

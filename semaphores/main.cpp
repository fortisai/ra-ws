int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg) {
    // ...
}

void pthread_exit(void *retval) {
    // ...
}

void pthread_join(pthread_t thread, void **retval) {
    // ...
}

int pthread_cancel(pthread_t thread) {
    // ...
}

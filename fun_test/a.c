#include <pthread.h>
#include <stdio.h>

void *thread_func(void *arg) {
    printf("Hello from a thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_func, NULL)) {
        printf("Error creating thread.\n");
        return 1;
    }
    printf("Thread created.\n");
    pthread_exit(NULL);
}

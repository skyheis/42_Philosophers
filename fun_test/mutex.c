/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:31:30 by ggiannit          #+#    #+#             */
/*   Updated: 2023/02/27 13:34:41 by ggiannit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

int shared_var = 0;
pthread_mutex_t mutex;

void *thread_func(void *arg) {
    // Acquire the mutex before accessing the shared variable
    pthread_mutex_lock(&mutex);
    shared_var++;
    printf("Thread %d incremented shared_var to %d\n", *(int *)arg, shared_var);
    // Release the mutex after accessing the shared variable
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[10];
    int thread_args[10];
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);
    // Create 10 threads to increment the shared variable
    for (int i = 0; i < 10; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_args[i]);
    }
    // Wait for all threads to complete
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}

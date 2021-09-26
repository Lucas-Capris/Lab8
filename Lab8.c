#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHREADS 4

// Variáveis globais
sem_t cond_1, cond_2;

// Thread 1
void *thread1 (void *t) {
    sem_wait(&cond_1);
    
    printf("Fique a vontade.\n");

    sem_post(&cond_1);
    sem_post(&cond_2);

    pthread_exit(NULL);
}

// Thread 2
void *thread2 (void *t) {

    printf("Seja bem-vindo!\n");

    sem_post(&cond_1);

    pthread_exit(NULL);
}

// Thread 3
void *thread3 (void *t) {
    sem_wait(&cond_2);
    sem_wait(&cond_2);

    printf("Volte sempre!\n");
    
    pthread_exit(NULL);
}

// Thread 4
void *thread4 (void *t) {
    sem_wait(&cond_1);

    printf("Sente-se por favor.\n");

    sem_post(&cond_1);
    sem_post(&cond_2);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int i;
    pthread_t threads[NTHREADS];

  // Inicialização dos semáforos
    sem_init(&cond_1, 0, 0);
    sem_init(&cond_2, 0, 0);

  // Criação das threads
    pthread_create(&threads[0], NULL, thread1, NULL);
    pthread_create(&threads[1], NULL, thread2, NULL);
    pthread_create(&threads[2], NULL, thread3, NULL);
    pthread_create(&threads[3], NULL, thread4, NULL);

  // Espera todas as threads completarem
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

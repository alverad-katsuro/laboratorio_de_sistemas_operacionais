#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMCONS  2
#define NUMPROD  2
#define BUFFERSIZE  1000
pthread_t cons[NUMCONS];
pthread_t prod[NUMPROD];
pthread_mutex_t buffer_mutex;
 int currentidx;
sem_t buffer_full, buffer_empty;
void *consumidor(void *arg);
void *produtor(void *arg);
int buffer[BUFFERSIZE];

int main(int argc, char **argv) {
  int i;
  srand48(time(NULL)); currentidx = 0;
  pthread_mutex_init(&buffer_mutex, NULL);
  sem_init(&buffer_full, 0, BUFFERSIZE);
  sem_init(&buffer_empty, 0, 0);
  for(i=0; i<NUMCONS; i++)
    pthread_create(&(cons[i]), NULL, consumidor, NULL);
  for(i=0; i<NUMPROD; i++)
    pthread_create(&(prod[i]), NULL, produtor, NULL);
  for(i=0; i<NUMCONS; i++)
    pthread_join(cons[i], NULL);
  for(i=0; i<NUMPROD; i++)
    pthread_join(prod[i], NULL);
}

void *produtor(void *arg) {
  int n;
  while(1) {
    n = (int)(drand48() * 1000.0);
    sem_wait(&buffer_full);
    pthread_mutex_lock(&buffer_mutex);
    buffer[currentidx++] = n;
    pthread_mutex_unlock(&buffer_mutex);
    sem_post(&buffer_empty);
    printf("Produzindo numero %d\n", n);
    sleep((int)(drand48() * 4.0));
  }
}

void *consumidor(void *arg) {
  int n;
  while(1) {
    sem_wait(&buffer_empty);
    pthread_mutex_lock(&buffer_mutex);
    n = buffer[--currentidx];
    pthread_mutex_unlock(&buffer_mutex);
    sem_post(&buffer_full);
    printf("Consumindo numero %d\n", n);
    sleep((int)(drand48() * 4.0));
  }
}

typedef struct {
pthread_mutex_t mutex;
sem_t waitsem;
int nthreads, current;
}barrier_t, *ptr_barrier_t;
void barrier_init(ptr_barrier_t, int);
void barrier(ptr_barrier_t);

void barrier_init(ptr_barrier_t pbarrier, int nt) {
pbarrier->nthreads = nt;
pbarrier->current = 0;
pthread_mutex_init(&(pbarrier->mutex), NULL);
sem_init(&(pbarrier->waitsem), 0, 0);
}

void barrier(ptr_barrier_t pbarrier) {
int i;
pthread_mutex_lock(&(pbarrier->mutex));
pbarrier->current++;
if(pbarrier->current < pbarrier->nthreads) {
pthread_mutex_unlock(&(pbarrier->mutex));
sem_wait(&(pbarrier->waitsem));
}else{
for(i=0; i<(pbarrier->nthreads - 1); i++)
sem_post(&(pbarrier->waitsem));
pbarrier->current = 0;
pthread_mutex_unlock(&(pbarrier->mutex));
}
}

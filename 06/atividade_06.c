#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


typedef struct conta {
  double saldo;
} Conta;
#define DEPOSITADORES 2
#define SACADORES 2

pthread_mutex_t mutex_var_saldo;
sem_t usando_conta;


void *realiza_deposito(void *);
void *realiza_saque(void *);

int main(int argc, char const *argv[]) {
  pthread_t depositador[DEPOSITADORES];
  pthread_t sacador[SACADORES];
  srand48(time(NULL));
  Conta conta;
  conta.saldo =0;
  sem_init(&usando_conta, 0, 0);
  pthread_mutex_init(&mutex_var_saldo, NULL);
  for (int i = 0; i < DEPOSITADORES; i++) {
    pthread_create(&(depositador[i]), NULL, realiza_deposito, (void *)&(conta));
  }
  for (int k = 0; k < SACADORES; k++) {
    pthread_create(&(sacador[k]), NULL, realiza_saque, (void *)&(conta));
  }
  for (int l = 0; l < DEPOSITADORES; l++) {
    pthread_join(&(depositador[l]), NULL);
  }
  for (int m = 0; m < SACADORES; m++) {
    pthread_join(&(sacador[m]), NULL);
  }
  printf("saldo final %0.2f\n", conta.saldo);
  
  return 0;
}

void *realiza_deposito(void *conta_ponteiro){
  Conta *conta = (Conta*) conta_ponteiro;
  for (int i = 0; i < 5; i++) {
    sem_wait(&usando_conta);
    pthread_mutex_lock(&mutex_var_saldo);
    conta->saldo += drand48() * 1000;
    pthread_mutex_unlock(&mutex_var_saldo);
    sem_post(&usando_conta);
    printf("saldo apos deposito %0.2f\n", conta->saldo);
  } 
  pthread_exit(NULL);
}

void *realiza_saque(void *conta_ponteiro) {
  Conta *conta = (Conta*) conta_ponteiro;
  for (int i = 0; i < 5; i++) {
    double valor = drand48() * 1000;
    while (valor > conta->saldo) {
      double valor = drand48() * 1000;
    }
    sem_wait(&usando_conta);
    pthread_mutex_lock(&mutex_var_saldo);
    conta->saldo -= valor;
    pthread_mutex_unlock(&mutex_var_saldo);
    sem_post(&usando_conta);
    printf("saldo apos o saque %0.2f\n", conta->saldo);
  }
  pthread_exit(NULL);
}

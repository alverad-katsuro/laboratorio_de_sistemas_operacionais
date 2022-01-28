#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>


typedef struct conta {
  double saldo;
} Conta;
#define DEPOSITADORES 1
#define SACADORES 1

pthread_mutex_t mutex_var_saldo;
sem_t usando_conta;
pthread_t depositador[DEPOSITADORES];
pthread_t sacador[SACADORES];


void *realiza_deposito(void *);
void *realiza_saque(void *);

int main(int argc, char const *argv[]) {
  int i;
  srand((unsigned)time(NULL));
  Conta conta;
  conta.saldo=10000;
  sem_init(&usando_conta, 0, 1);
  pthread_mutex_init(&mutex_var_saldo, NULL);
  printf("saldo inicial %0.2f\n", conta.saldo);
  for (i = 0; i < DEPOSITADORES; i++) {
    pthread_create(&(depositador[i]), NULL, realiza_deposito, (void *)&(conta));
  }
  for (i = 0; i < SACADORES; i++) {
    pthread_create(&(sacador[i]), NULL, realiza_saque, (void *)&(conta));
  }
  for (i = 0; i < DEPOSITADORES; i++) {
    pthread_join(depositador[i], NULL);
  }
  for (i = 0; i < SACADORES; i++) {
    pthread_join(sacador[i], NULL);
  }
  printf("saldo final %0.2f\n", conta.saldo);
  
  return 0;
}

double valor_random(){
  return (100 + ((rand() % 401) + ((rand() % 10) / 11.0)));
}

double valor_saque(int saldo){
  while (1) {
    double valor = valor_random();
    if (valor <= saldo) {
      return valor;
    }
  }
}

void *realiza_deposito(void *conta_ponteiro){
  Conta *conta = (Conta*) conta_ponteiro;
  for (int i = 0; i < 5; i++) {
    sem_wait(&usando_conta);
    pthread_mutex_lock(&mutex_var_saldo);
    conta->saldo += valor_random();
    pthread_mutex_unlock(&mutex_var_saldo);
    sem_post(&usando_conta);
    printf("saldo apos deposito %0.2f\n", conta->saldo);
    sleep((int)(rand() % 5));
  } 
  pthread_exit(NULL);
}

void *realiza_saque(void *conta_ponteiro) {
  Conta *conta = (Conta*) conta_ponteiro;
  for (int i = 0; i < 5; i++) {
    double valor = valor_saque(conta->saldo);
    sem_wait(&usando_conta);
    pthread_mutex_lock(&mutex_var_saldo);
    conta->saldo -= valor;
    pthread_mutex_unlock(&mutex_var_saldo);
    sem_post(&usando_conta);
    printf("saldo apos o saque %0.2f\n", conta->saldo);
    sleep((int)(rand() % 5));
  }
  pthread_exit(NULL);
}

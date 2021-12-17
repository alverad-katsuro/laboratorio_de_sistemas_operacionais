#include "process.h"
#include <stdlib.h>

void createProcess(int id, int time, int nice, Escalonador* escalonador){
  Process* processo = malloc(sizeof(Process));
  processo->id = id;
  processo->time = time;
  processo->nice = nice;
  Insere(processo, escalonador->processos);
}

Escalonador* createEscalonador(int tempo){
  Escalonador* escalonador = malloc(sizeof(Escalonador));
  escalonador->tempo = tempo;
  escalonador->processos = inicializa();
  return escalonador;
}

void escalonaProcess(Escalonador* escalonador){
  int process_end = 0;
  while ((escalonador->processos->ultimo - escalonador->processos->primeiro) != process_end){
    process_end = 0;
    for (int i = 0; i < escalonador->processos->ultimo; i++){
      if (escalonador->processos->item[i].time > escalonador->tempo){
        printf("P%d, %d; ", escalonador->processos->item[i].id, escalonador->tempo);
        escalonador->processos->item[i].time -= escalonador->tempo;
      } else {
        if (escalonador->processos->item[i].time > 0){
          printf("P%d, %d*; ", escalonador->processos->item[i].id, escalonador->processos->item[i].time);
          escalonador->processos->item[i].time = 0;
          Retira(escalonador->processos, i);
          i--;
        } else if (escalonador->processos->item[i].time == 0) {
          process_end++;
        }
      }
      if (i == (escalonador->processos->ultimo - 1)) {
        printf("\n");
      }
    } 
  }
}

void escalonaProcessPrio(Escalonador* escalonador){
  // Contrala a faixa de prioridade
  int faixa_prio = 0;
  while (faixa_prio <= 20){
    // Verifica se existe proc na faixa
    int proc_faixa_exist = 1;
    while (proc_faixa_exist) {
      proc_faixa_exist = 0;
      for (int i = 0; i < escalonador->processos->ultimo; i++) {
        // Verifica se existe na faixa
        if (escalonador->processos->item[i].nice == faixa_prio) {
          proc_faixa_exist = 1;
          if (escalonador->processos->item[i].time > escalonador->tempo){
            printf("P%d, %d; ", escalonador->processos->item[i].id, escalonador->tempo);
            escalonador->processos->item[i].time -= escalonador->tempo;
          } else {
            if (escalonador->processos->item[i].time > 0){
              printf("P%d, %d*; ", escalonador->processos->item[i].id, escalonador->processos->item[i].time);
              escalonador->processos->item[i].time = 0;
              Retira(escalonador->processos, i);
            }
          }
          if (i == (escalonador->processos->ultimo - 1)) {
            printf("\n");
          }
        }
      }
    }
    faixa_prio++;
  }
}

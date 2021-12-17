#include "Lista_linear.c"

typedef struct escalonador{
  // Tempo de processamento
  int tempo;
  // Lista de Processos
  ListaLinear *processos;
}Escalonador;


void createProcess(int, int, int, Escalonador*);
Escalonador* createEscalonador(int);
//void escalonaProcess(Process*);

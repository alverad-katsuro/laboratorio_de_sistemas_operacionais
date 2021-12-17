#include <stdio.h>
#include <stdlib.h>
#include "Lista_linear.h"

ListaLinear* inicializa(){
  ListaLinear* lista = (ListaLinear*) malloc(sizeof(ListaLinear));
  lista->item;
  lista->primeiro = 0;
  lista->ultimo = 0;
  return lista;
}

void FLVazia(ListaLinear* lista){
  lista->primeiro = InicioVetor;
  lista->ultimo = lista->primeiro;
}

void Insere(Process *x, ListaLinear* lista){
  if (lista->ultimo >= MaxTam){
    printf("Lista cheia \n");
  } else {
    lista->item[lista->ultimo] = *x;
    lista->ultimo++;
  }
}

Process* Retira(ListaLinear* lista, Posicao index){
  if (Vazia(lista) || index > lista->ultimo){
    printf("Posição inexistente\n");
    return NULL;
  }
  Process* item = malloc(sizeof(Process));
  item = &lista->item[index];
  for (int i = 0; i < lista->ultimo; i++) {
    if (i >= index && i < lista->ultimo) {
      lista->item[i] = lista->item[i+1];
    }
  }
  lista->ultimo--;
  return item;
}

int Vazia(ListaLinear* lista){
  if (lista->primeiro == lista->ultimo){
    return 1;
  } else {
    return 0;
  }
}

void Imprime(ListaLinear* lista){
  for (int i = 0; i < lista->ultimo; i++){
    printf("O processo %d tem time %d e nice %d \n", lista->item[i].id, lista->item[i].time, lista->item[i].nice);
  } 
}
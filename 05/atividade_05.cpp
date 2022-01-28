#include<stdio.h>
#include<unistd.h>
#include "inverse.cpp"
//#include "matriz.h"
#include "multiplacao_matriz.c"

Matriz* cria_matriz_ponteiro(int linhas, int colunas){
  Matriz *tipo_matriz = (Matriz *)malloc(sizeof(Matriz));
  tipo_matriz->colunas = colunas;
  tipo_matriz->linhas = linhas;
  tipo_matriz->matriz = (float **)malloc(sizeof(float*) * tipo_matriz->linhas);
  for (int i = 0; i < tipo_matriz->linhas; i++) {
    tipo_matriz->matriz[i] = (float *)malloc(sizeof(float) * tipo_matriz->colunas);
  }
  return tipo_matriz;
}

int main(int argc, char const *argv[]) {
  const int dimensao = 7;
  Matriz *a = cria_matriz_ponteiro(dimensao, dimensao);
  Matriz *b = cria_matriz_ponteiro(dimensao, dimensao);
  int pipe_comumnication[2];
  pipe(pipe_comumnication);
  if (a->linhas == b->colunas) {
    if (fork()) {
      close(pipe_comumnication[0]);
      int add_matriz_b[dimensao][dimensao] = {
        {2,3,5,1,5,5,5},
        {6,9,5,2,2,6,5},
        {6,4,9,8,9,2,6},
        {8,8,9,3,4,6,2},
        {8,5,2,1,7,7,7},
        {1,4,6,4,8,8,7},
        {9,2,2,6,1,9,1}
      };
      for (int i = 0; i < dimensao; i++) {
        for (int k = 0; k < dimensao; k++) {
          b->matriz[i][k] = add_matriz_b[i][k];
        }
      }
      if (determinant(b->matriz, b->colunas) == 0) {
        printf("Matriz b não tem determinante\n");
        exit(1);
      } else {
        b->matriz = cofactor(b->matriz, b->colunas);
        write(pipe_comumnication[1], &b, sizeof(b));
      }
    } else{
        close(pipe_comumnication[1]);
        int add_matriz_a[dimensao][dimensao] = {
        {2,3,5,1,5,5,5},
        {6,9,5,2,2,6,5},
        {6,4,9,8,9,2,6},
        {8,8,9,3,4,6,2},
        {8,5,2,1,7,7,7},
        {1,4,6,4,8,8,7},
        {9,2,2,6,1,9,1}
        };
        for (int i = 0; i < dimensao; i++) {
          for (int k = 0; k < dimensao; k++) {
            a->matriz[i][k] = add_matriz_a[i][k];
          }
        }
      if (determinant(a->matriz, a->colunas) == 0) {
        printf("Matriz A não tem determinante\n");
        exit(1);
      } else {
        a->matriz = cofactor(a->matriz, a->colunas);
        read(pipe_comumnication[0], &b, sizeof(b));
        mulMat(a, b);
      }
    }
  }
  return 0;
}

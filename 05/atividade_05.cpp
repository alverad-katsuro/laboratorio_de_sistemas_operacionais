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
  const int dimensao = 10;
  Matriz *a = cria_matriz_ponteiro(dimensao, dimensao);
  Matriz *b = cria_matriz_ponteiro(dimensao, dimensao);
  int pipe_comumnication[2];
  pipe(pipe_comumnication);
  if (a->linhas == b->colunas) {
    if (fork()) {
      close(pipe_comumnication[0]);
      int add_matriz_b[dimensao][dimensao] = {
        {2,6,3,4,3,1,7,9,5,9},
        {2,7,5,6,6,5,3,1,1,8},
        {7,2,5,2,1,6,7,5,7,6},
        {2,1,1,3,4,6,9,3,8,7},
        {4,6,3,7,3,2,7,8,6,4},
        {2,3,4,3,6,5,5,1,3,1},
        {5,3,3,2,1,3,2,9,7,2},
        {2,1,5,6,2,9,7,5,5,8},
        {7,8,4,4,1,5,6,1,2,6},
        {5,7,3,5,4,3,8,4,8,3}
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
          {2,6,3,4,3,1,7,9,5,9},
          {2,7,5,6,6,5,3,1,1,8},
          {7,2,5,2,1,6,7,5,7,6},
          {2,1,1,3,4,6,9,3,8,7},
          {4,6,3,7,3,2,7,8,6,4},
          {2,3,4,3,6,5,5,1,3,1},
          {5,3,3,2,1,3,2,9,7,2},
          {2,1,5,6,2,9,7,5,5,8},
          {7,8,4,4,1,5,6,1,2,6},
          {5,7,3,5,4,3,8,4,8,3}
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

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
  Matriz *a = cria_matriz_ponteiro(3, 3);
  Matriz *b = cria_matriz_ponteiro(3, 3);
  int pipe_comumnication[2];
  pipe(pipe_comumnication);
  if (a->linhas == b->colunas) {
    if (fork()) {
      close(pipe_comumnication[0]);
      b->matriz[0][0] = 1;
      b->matriz[0][1] = 9;
      b->matriz[0][2] = 5;
      b->matriz[1][0] = 3;
      b->matriz[1][1] = 7;
      b->matriz[1][2] = 8;
      b->matriz[2][0] = 10;
      b->matriz[2][1] = 4;
      b->matriz[2][2] = 2;
      if (determinant(b->matriz, b->colunas) == 0) {
        printf("Matriz b não tem determinante\n");
        exit(1);
      } else {
        b->matriz = cofactor(b->matriz, b->colunas);
        write(pipe_comumnication[1], &b, sizeof(b));
        sleep(10);
      }
    } else{
        close(pipe_comumnication[1]);
        a->matriz[0][0] = 1;
        a->matriz[0][1] = 9;
        a->matriz[0][2] = 5;
        a->matriz[1][0] = 3;
        a->matriz[1][1] = 7;
        a->matriz[1][2] = 8;
        a->matriz[2][0] = 10;
        a->matriz[2][1] = 4;
        a->matriz[2][2] = 2;
      if (determinant(a->matriz, a->colunas) == 0) {
        printf("Matriz A não tem determinante\n");
        exit(1);
      } else {
        a->matriz = cofactor(a->matriz, a->colunas);
        read(pipe_comumnication[0], &b, sizeof(b));
        sleep(10);
        mulMat(a, b);
      }
    }
  }
  return 0;
}

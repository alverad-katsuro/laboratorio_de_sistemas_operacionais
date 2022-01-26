#include <stdio.h>
#include "matriz.h"
 

void mulMat(Matriz *matrizA, Matriz *matrizB) {
  float rslt[matrizA->linhas][matrizB->colunas];

  printf("Multiplication of given two matrices is:\n\n");

  for (int i = 0; i < matrizA->linhas; i++) {
    for (int j = 0; j < matrizB->colunas; j++) {
      rslt[i][j] = 0;
      for (int k = 0; k < matrizB->linhas; k++) {
          rslt[i][j] += matrizA->matriz[i][k] * matrizA->matriz[k][j];
      }
      printf("%f\t", rslt[i][j]);
    }
    printf("\n");
  }
}
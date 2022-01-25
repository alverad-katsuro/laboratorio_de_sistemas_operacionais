#include <stdio.h>
#include <stdlib.h>

int **matrizExemplo()
{
    int **vet;
    
    int tamVetor = 10;
    vet = (int **)malloc(sizeof(int *)*tamVetor);
    for (int i = 0; i < 10; i++) {
      vet[i] = i;
    }
    return vet;
}

int main()
{
    int **retorno;

    retorno = matrizExemplo();

    printf("Retorno e: %d\n", retorno[9]);
    
    free(retorno);
    
    return 0;
}
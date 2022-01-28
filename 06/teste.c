#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void teste(){
  printf("Numero: %.2f\n", rand() % 1001 + ((rand() % 10) / 11.0));
}

int main()
{
    int i;
    printf("intervalo da rand: [0,%d]\n", RAND_MAX);
    srand((unsigned)(time(NULL)));
    while (1)
    {
      teste();
    }
    
}


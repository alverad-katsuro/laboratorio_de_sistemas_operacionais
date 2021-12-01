#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//protótipo da função fatorial
double fatorial(int n);
int main(void)
{
  int numero;
  double f;
  
  printf("Digite o numero que deseja calcular o fatorial: ");
  scanf("%d",&numero);
  
  //chamada da função fatorial
  f = fatorial(numero);
  
  printf("Fatorial de %d = %f \n", numero, f);
  
  return 0;
}
//Função recursiva que calcula o fatorial
//de um numero inteiro n
static double *vfat;

double fatorial(int n)
{
  vfat = mmap(vfat, sizeof *vfat, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
  
  if ( n <= 1 )
    //Caso base: fatorial de n <= 1 retorna 1
    return (1);
  else
  {
    //Chamada recursiva
    pid_t pid = fork();
    if (pid == 0) {
      printf("entro")
      *vfat = n * fatorial(n - 1);
      exit(0);
    }
    waitpid(pid, 0, WNOHANG);

    return (*vfat);
  }
}
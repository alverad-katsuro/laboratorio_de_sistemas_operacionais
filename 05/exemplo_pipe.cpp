#include<stdio.h>
#include<unistd.h>
#include "lista_encandeada/Lista_encadeada.cpp"
#define BUFSIZE 100

int main(void) {
  int fd[2];
  int i;
  int matriz[2][2];
  Estado estado;
  pipe(fd);
  /* fd[0] - leitura, fd[1] - escrita*/
  if (fork() == 0) {
    close(fd[0]);
    for (i=0; i < 10; i++) {
    }
    matriz[0][0] = 21;
    matriz[0][1] = 23;
    matriz[1][0] = 24;
    matriz[1][1] = 25;
    //sprintf(line,"teste %d",n);
    write(fd[1], &matriz, sizeof(int[2][2]));
    //printf("Processo FILHO escreve na lista: %d\n", matriz[i]);
    //sleep(1);
  } else {
    close(fd[1]);
    for (i=0; i < 10; i++) {
      //printf("\t\t\t Processo PAI realiza a leitura do pipe\n");
    }
      read(fd[0], &matriz, sizeof(int[2][2]));
      //sscanf(line,"aa %d",&n);
      for (int i = 0; i < 2; i++) {
        for (int k = 0; k < 2; k++) {
          printf("\t%d ", matriz[i][k]);
        }
        printf("\n"); 
      }
      
      //printf("\t\t\t Processo PAI lê da listaaaaa: %d\n", pop_first(&lista));
      sleep(1);
  }
}

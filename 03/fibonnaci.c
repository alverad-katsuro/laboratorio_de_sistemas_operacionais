#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void fiboo(int x){
  int t1 = 0, t2 = 1;

  int nextTerm = t1 + t2;

  for (int i = 3; i <= x; ++i) {
    t1 = t2;
    t2 = nextTerm;
    nextTerm = t1 + t2;
  }

  printf("\033[1;34mNa posição %d, o fibonace vale: %d \n", x, nextTerm);
}


int main() {
  int n;
  printf("Insira o numero de fibonaces a serem calculados: ");
  scanf("%d", &n);
  pid_t pid = fork();
  if (pid > 1) {
    printf("\033[1;33mPai: %d \n", getpid());
    printf("\033[1;33mEstamos calculando para você, seu preguiçoso\n");
  } else {
    printf("\033[1;35mMinha pid filho é: %d \n", getpid());
    for (int i = 0; i < n; i++){
      pid_t pid_filho = fork();
      if (pid_filho == 0){
        printf("\033[1;36mMinha pid neto é: %d \n", getpid());
        fiboo(i);
        exit(0);
      }
    }
    exit(0);
  }
  return 0;
}
#include <stdio.h>
#include "process.c"

int main(int argc, char const *argv[]) {
  Escalonador* escalonador = createEscalonador(10);
  createProcess(1, 200, 20, escalonador);
  createProcess(2, 300, 10, escalonador);
  createProcess(3, 25, 0, escalonador);
  escalonaProcessPrio(escalonador);
  return 0;
}

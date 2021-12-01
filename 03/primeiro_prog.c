#include <stdio.h>

int main()
{
  int n, i;
  long fatorial;
  printf("Entre o valor de n (0 <= n < 20): ");
  scanf("%d", &n);
  fatorial = 1;
  i = 1;
  while (i <= n) {
    fatorial = fatorial * i;
    i++;
  }
  printf("%d! = %ld\n", n, fatorial);
  return 0;
}
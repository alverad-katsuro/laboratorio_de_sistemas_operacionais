#include<stdio.h>
#include<stdlib.h>

typedef struct aa {
  int valor;
  int valor2;
} Aa;


void *teste_dv(void *varg) {

}

int main()
{
    // Declaring a pointer to store address
    // pointing to an array of size 3
    int(*p)[3];
  
    // Define an array of size 3
    int a[3] = { 1, 2, 3 };
  
    // Store the base address of the
    // array in the pointer variable
    p = &a;
  
    // Print the results
    for (int i = 0; i < 3; i++)
    {
      printf("%d\n", *((*p) + i));
    }
    
    return 0;
}




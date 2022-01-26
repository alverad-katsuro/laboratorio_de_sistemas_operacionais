#include<stdio.h>
#include<math.h>

float determinant(float **, int);
float** cofactor(float **, int);
float** transpose(float **, float [][25], int);

float** cria_matriz(int x, int y){
  float** matriz = (float **)malloc(sizeof(float*) * x);
  for (int i = 0; i < y; i++) {
    matriz[i] = (float *)malloc(sizeof(float) * y);
  }
  return matriz;
}

/*
int main()
{
  float  d;
  int i, j, tamanho;
  printf("Enter the order of the Matrix '': ");
  scanf("%d", &tamanho);
  float **matriz = cria_matriz(tamanho, tamanho);
  printf("Enter the elements of %dX%d Matrix : \n", tamanho, tamanho);
  for (i = 0;i < tamanho; i++)
    {
     for (j = 0;j < tamanho; j++)
       {
        scanf("%f", &matriz[i][j]);
        }
    }
  d = determinant(matriz, tamanho);
  if (d == 0){
    printf("\nInverse of Entered Matrix is not possible\n");
  } else {
   float **outra_coisa = cofactor(matriz, tamanho);
  }
}
*/

/*For calculating Determinant of the Matrix */
float determinant(float **matriz, int tamanho) {
  float **b = cria_matriz(25, 25);
  float s = 1, det = 0;
  int i, j, m, n, c;
  if (tamanho == 1)
    {
     return (matriz[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < tamanho; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < tamanho; i++)
          {
            for (j = 0 ;j < tamanho; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = matriz[i][j];
                   if (n < (tamanho - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (matriz[0][c] * determinant(b, tamanho - 1));
          s = -1 * s;
          }
    }
    return (det);
}
 
float** cofactor(float **num, int f)
{
 float fac[25][25];
 float **b = cria_matriz(25,25);
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  return transpose(num, fac, f);
}

/*Finding transpose of matrix*/ 
float** transpose(float **num, float fac[25][25], int r)
{
  int i, j;
  float d;
  float **inverse = cria_matriz(25, 25);
  float **b = cria_matriz(25, 25);
 
  for (i = 0;i < r; i++) {
    for (j = 0;j < r; j++) {
      b[i][j] = fac[j][i];
    }
  }
  d = determinant(num, r);
  for (i = 0;i < r; i++){
    for (j = 0;j < r; j++) {
      inverse[i][j] = b[i][j] / d;
    }
  }
  /*
  printf("The inverse of matrix is : \n");
 
  for (i = 0;i < r; i++) {
    for (j = 0;j < r; j++) {
      printf("\t%f", inverse[i][j]);
    }
    printf("\n");
  }
  */
  return inverse;
}


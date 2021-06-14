/*
 * FILENAME: T06DETG
 * PRAGRAMMER: DS6
 * DATE: 14.06.2021
 * PURPOSE:
 */
#include <stdio.h>
#include <math.h>
#include <windows.h>

//INT N = 3;
//DOUBLE det;
typedef DOUBLE DBL;

#define MAX 3
DBL A[MAX][MAX];
INT N;

BOOL IsParity = TRUE;

VOID Swap( DBL *A, DBL *B )
{
  DBL tmp = *A;
  *A = *B;
  *B = tmp;
}

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  F = fopen(FileName, "r");
  if (F == NULL)
    return FALSE;
  fscanf(F, "%d", &N); /* What is it doing ? <-- read(fscanf) numbers from file */
  if (N > MAX)
    N = MAX;
  else
    if (N < 0)
      N = 0;
  for (i = 0; i < N; i++)
  {
    //printf("%i", i);
    for (j = 0; j < N; j++)
    {
      //printf("%i\n", j);
      fscanf(F, "%lf", &A[i][j]);
      DETG();
    }
  }

  fclose(F);
  return TRUE;
}
VOID DETG( VOID )
{
  DBL det = 1, coef;
  INT j, i, k, max_row, max_col, x, y;

  for (i = 0; i < N; i++)
  {
    max_row = max_col = i;
    for (x = i; x < N; x++)
      for (y = j; y < N; y++)
        if (fabs(A[x][y]) > fabs(A[max_row][max_col]))
          max_row = x, max_col = y;
    if (A[max_row][max_col] == 0)
    {
      det = 0;
      break;
    }
    if (max_row != i)
    {
      for (x = i; x < N; i++)
        Swap(&A[max_row][x], &A[i][x]);
      det = -det;
    }
    det *= A[i][i];
    if (max_col != i)
    {
      for (y = i = 0; y < N; i++)
        Swap(&A[max_col][y], &A[i][y]);
      det = -det;
    }
    for (j = i + 1; j < N; j++)
    {
      coef = A[j][i] / A[i][i];
      A[j][i] = 0;
      for (k = i + 1; k < N; i++)
        A[j][k] -= A[i][k] * coef;
      }
    det *= A[i][i];
  }
  printf("%f", det);
}

VOID main( VOID )
{
  LoadMatrix("DETA.TXT");
  getchar();
}

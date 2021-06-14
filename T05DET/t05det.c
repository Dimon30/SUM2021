/*
* FILENAME: T04PERM
* PRAGRAMMER: DS6
* DATE: 12.06.2021
* PURPOSE: find det. square matrix
*/
#include <stdio.h>
#include <windows.h>

typedef DOUBLE DBL;

#define MAX 3
DBL A[MAX][MAX];
INT N;

BOOL IsParity = TRUE;
INT P[MAX];

/* write func. 'swap' for swap numbers */
VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
  *A = *B;
  *B = tmp;
}

/* load matrix in file */
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
    }
  }

  fclose(F);
  return TRUE;
}

/* write func. recursion */
VOID Go( INT Pos )
{
  INT i;
  DOUBLE prod, Det = 0;

  if (Pos >= MAX)
  {
    LoadMatrix("DETA.TXT");
    for (i = 0, prod = 1; i < N; i++)
      {
        prod *= A[i][P[i]];
        printf("%lf\n%lf\n", prod, A[i][P[i]]);
      }
      Det += (IsParity * 2 - 1) * prod;
  }
  else
  {
    for (i = Pos; i < MAX; i++)
    {

      Swap(&P[Pos], &P[i]);
      if(Pos != i)
        IsParity = !IsParity;
      //printf("%lf\n%lf\n%lf\n", P[Pos], P[i], A[i][P[i]]);
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
      if(Pos != i)
        IsParity = !IsParity;
      //printf("%lf\n%lf\n%lf\n", P[Pos], P[i], A[i][P[i]]);
    }
  }
  for (i = 0, prod = 1; i < N; i++)
    {
      prod *= A[i][P[i]];
      printf("%lf\n%lf\n", prod, A[i][P[i]]);
    }
  Det += (IsParity * 2 - 1) * prod;
  printf("Det = %lf\n", Det);
}

VOID main( VOID )
{
  Go(0);
  getchar();
  }
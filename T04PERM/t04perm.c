/*
 * FILENAME: T04PERM
 * PRAGRAMMER: DS6
 * DATE: 12.06.2021
 * PURPOSE:
 */
#include <stdio.h>

#include <windows.h>

#define MAX 3

INT P[MAX];
BOOL IsParity = TRUE;

VOID Swap( INT *A, INT *B )
{
  INT tmp = *A;
  *A = *B;
  *B = tmp;
}

/* Store permution to log file function */
VOID Store( VOID )
{
  FILE *F;
  INT i;

  F = fopen("PERM.TXT", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX - 1; i++)
    fprintf(F, "%d,", P[i]);
  fprintf(F, "%d - parity: %s\n", P[MAX - 1], IsParity ? "even" : "odd");

  fclose(F);
}/* End of 'Store' function */

VOID Go( INT Pos )
{
  INT i;

  if (Pos >= MAX)
    Store();
  else
  {
    for (i = Pos; i < MAX; i++)
    {

      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        IsParity = !IsParity;
      Go(Pos + 1);
      Swap(&P[Pos], &P[i]);
      if (Pos != i)
        IsParity = !IsParity;
    }
  }
}
VOID main ( VOID )
{
  INT i;

  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  Go(0);
  //Store();
  //getchar();
}
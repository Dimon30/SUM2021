#include "rndres.h"

VOID DS6_RndResInit( VOID )
{
  DS6_RndShadersInit();
  DS6_RndTexInit();
  DS6_RndMtlInit();
}
VOID DS6_RndResClose( VOID )
{
  DS6_RndMtlClose();
  DS6_RndShadersClose();
  DS6_RndTexClose();
}
/* FILE NAME: anim.c
 * PROGRAMMER: DS6
 * DATE: 22.06.2021
 * PURPOSE: .
 */

#include "anim.h"

ds6ANIM DS6_Anim;

VOID DS6_AnimInit( HWND hWnd )
{
  DS6_RndInit(hWnd);
  DS6_Anim.hWnd = hWnd;

  DS6_TimerInit();
  DS6_AnimInputInit();

}

VOID DS6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < DS6_Anim.NumOfUnits; i++)
  {
    DS6_Anim.Units[i]->Close(DS6_Anim.Units[i], &DS6_Anim);
    free(DS6_Anim.Units[i]);
    DS6_Anim.Units[i] = NULL;
  }
  DS6_Anim.NumOfUnits = 0;
  DS6_RndClose();
}

VOID DS6_AnimResize( INT W, INT H )
{
  DS6_Anim.W = W;
  DS6_Anim.H = H;
  DS6_RndResize(W, H);
}

VOID DS6_AnimCopyFrame( VOID )
{
  DS6_RndCopyFrame();
}

VOID DS6_AnimRender( VOID )
{
  INT i;

  DS6_TimerResponse();
  DS6_AnimInputResponse();

  for (i = 0; i < DS6_Anim.NumOfUnits; i++)
    DS6_Anim.Units[i]->Response(DS6_Anim.Units[i], &DS6_Anim);

  /* scene rendering */
  DS6_RndStart();
  for (i = 0; i < DS6_Anim.NumOfUnits; i++)
    DS6_Anim.Units[i]->Render(DS6_Anim.Units[i], &DS6_Anim);

  DS6_RndEnd();
}

VOID DS6_AnimUnitAdd( ds6UNIT *Uni )
{
  if (DS6_Anim.NumOfUnits < DS6_MAX_UNITS)
    DS6_Anim.Units[DS6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &DS6_Anim);
}

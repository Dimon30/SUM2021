#include <stdio.h>
#include "units.h"

typedef struct tagds6UNIT_CONTROL
{
  DS6_UNIT_BASE_FIELDS;
  DBL CamDist, RotX, RotY;
}ds6UNIT_CONTROL;

static VOID DS6_UnitInit( ds6UNIT_CONTROL *Uni, ds6ANIM *Ani )
{
  Uni->CamDist = 75;
  Uni->RotX = -D2R(45);
  Uni->RotY = D2R(45);
}

static VOID DS6_UnitResponse( ds6UNIT_CONTROL *Uni, ds6ANIM *Ani )
{
  //VEC Loc = PointTransform(DS6_RndCamLoc, MatrMulMatr(MatrRotateX(-18 / 2.0 * Uni->RotX), MatrRotateY(-102 / 8.0 * Uni->RotY)));
  //VEC Dir = VecSubVec(VecSet1(0), Loc);
  /*
  if(Ani->KeysClick[VK_RETURN] && Ani->Keys[VK_MENU])
    DS6_AnimFlipFullScreen();
  
  if(Ani->Keys['P'] && Ani->Keys[VK_CONTROL])
    Ani->ISPause = !Ani->ISPause;

  if(Ani->Keys[VK_ESCAPE])
    DS6_AnimDoExit();
  */
  /*Uni->RotX += Ani->Mdy * Ani->GlobalDeltaTime * Ani->Keys[VK_LBUTTON];*/
  /* Uni->RotY += Ani->Mdx * Ani->GlobalDeltaTime * Ani->Keys[VK_LBUTTON];*/
  Uni->RotX += Ani->JZ * Ani->GlobalDeltaTime * -3.5;
  Uni->RotY += Ani->JR * Ani->GlobalDeltaTime * -3.5;
  /*if (Ani->JBut[5] > 0)
    Loc = VecAddVec(Loc, VecMulNum(Dir, Ani->GlobalDeltaTime));
  if (Ani->JBut[4] > 0)
    Loc = VecSubVec(Loc, VecMulNum(Dir, Ani->GlobalDeltaTime));
  */
  //Uni->CamDist += Ani->Mdz * Ani->GlobalDeltaTime;
  DS6_RndCamSet(PointTransform(VecSet(0, 0, Uni->CamDist), MatrMulMatr(MatrRotateX(-18 / 2.0 * Uni->RotX), MatrRotateY(-102 / 8.0 * Uni->RotY))), VecSet1(0), VecSet(0, 1, 0));
  //DS6_RndCamSet(Loc, VecSet1(0), VecSet(0, 1, 0));

  //DS6_RndCamLoc.X += Ani->GlobalDeltaTime * Ani->JX * 30;

  //DS6_RndCamSet(DS6_RndCamLoc, VecSet(0, 0, 0), VecSet(0, 1, 0));
}

/*
 * Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT_COW *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitClose( ds6UNIT_CONTROL *Uni, ds6ANIM *Ani )
{
} /* End of 'DS6_UnitClose' function */

/*
 * Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT_COW *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitRender( ds6UNIT_CONTROL *Uni, ds6ANIM *Ani )
{
} /* End of 'DS6_UnitRender' function */


ds6UNIT * DS6_UnitCreateControl( VOID )
{
  ds6UNIT *Uni;

  if((Uni = DS6_AnimUnitCreate(sizeof(ds6UNIT_CONTROL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)DS6_UnitInit;
  Uni->Close = (VOID *)DS6_UnitClose;
  Uni->Response = (VOID *)DS6_UnitResponse;
  Uni->Render = (VOID *)DS6_UnitRender;
  return Uni;
}

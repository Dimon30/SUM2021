#include <stdio.h>
#include "units.h"

typedef struct tagds6UNIT_CONTROL
{
  DS6_UNIT_BASE_FIELDS;
  DBL CamDist, RotX, RotY, RotEl, RotAz;
}ds6UNIT_CONTROL;

static VOID DS6_UnitInit( ds6UNIT_CONTROL *Uni, ds6ANIM *Ani )
{
  Uni->CamDist = 75;
  Uni->RotX = -D2R(0);
  Uni->RotY = D2R(0);
}

static VOID DS6_UnitResponse( ds6UNIT_CONTROL *Uni, ds6ANIM *Ani )
{
  VEC Loc;
  VEC Dir;
  VEC a;

  /*
  if(Ani->KeysClick[VK_RETURN] && Ani->Keys[VK_MENU])
    DS6_AnimFlipFullScreen();
  
  if(Ani->Keys['P'] && Ani->Keys[VK_CONTROL])
    Ani->ISPause = !Ani->ISPause;

  if(Ani->Keys[VK_ESCAPE])
    DS6_AnimDoExit();
  */

  Uni->RotEl += Ani->Mdy * Ani->GlobalDeltaTime;
  Uni->RotAz += Ani->Mdx * Ani->GlobalDeltaTime;
  Uni->RotX += Ani->JZ * Ani->GlobalDeltaTime * -75.0;
  Uni->RotY += Ani->JR * Ani->GlobalDeltaTime * -75.0;
  if (Ani->JBut[5] > 0)
  {
    Loc = VecSet(0, 0, Uni->CamDist);
    Dir = VecSubVec(VecSet1(0), Loc);
    a = VecSubVec(Dir, VecMulNum(VecNormalize(Dir), Ani->GlobalDeltaTime));
    DS6_RndCamSet(PointTransform(VecSet(0, 0, Uni->CamDist), MatrTranslate(a)), VecSet1(0), VecSet(0, 1, 0));
  }
  if (Ani->JBut[4] > 0)
  {
    Loc = VecSet(0, 0, Uni->CamDist);
    Dir = VecSubVec(VecSet1(0), Loc);
    Dir = VecAddVec(Dir, VecMulNum(VecNormalize(Dir), Ani->GlobalDeltaTime));
    DS6_RndCamSet(PointTransform(VecSet(0, 0, Uni->CamDist), MatrMulMatr(MatrScale(VecSet1(Ani->GlobalDeltaTime)), MatrTranslate(Dir))), VecSet1(0), VecSet(0, 1, 0));
  }


  DS6_RndCamSet(PointTransform(VecSet(0, 0, Uni->CamDist), MatrMulMatr(MatrRotateX(Uni->RotX), MatrRotateY( Uni->RotY))), VecSet1(0), VecSet(0, 1, 0));
  DS6_RndCamSet(VecMulMatr(VecSet(0, 0, Uni->CamDist), MatrMulMatr3(MatrRotateX(Uni->RotEl), MatrRotateY(Uni->RotAz), MatrTranslate(VecSet1(0))), VecSet1(0), VecSet(0, 1, 0));
  //  DS6_RndCamSet(Loc, VecSet1(0), VecSet(0, 1, 0));
  if (Ani->JButClick[3] > 0)
  {
    DS6_AnimUnitAdd(DS6_UnitCreateFireBall());
  }

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

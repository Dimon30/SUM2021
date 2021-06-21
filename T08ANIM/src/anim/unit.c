/*
 * FILE NAME: unit.c
 * PROGRAMMER: DS6
 * DATE: 19.06.2021
 * PURPOSE: implementation of animation object handling.
 */

#include "anim.h"
/*
 * Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitInit( ds6UNIT *Uni, ds6ANIM *Ani )
{
} /* End of 'DS6_UnitInit' function */

/*
 * Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitClose( ds6UNIT *Uni, ds6ANIM *Ani )
{
} /* End of 'DS6_UnitClose' function */

/*
 * Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitResponse( ds6UNIT *Uni, ds6ANIM *Ani )
{
} /* End of 'DS6_UnitResponse' function */

/*
 * Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitRender( ds6UNIT *Uni, ds6ANIM *Ani )
{
} /* End of 'DS6_UnitRender' function */

/*
 * Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *      INT Size;
 * RETURNS: 
     (ds6UNIT *) pointer to created unit.
 */
ds6UNIT * DS6_AnimUnitCreate( INT Size )
{
  ds6UNIT *Uni;
 /* memory allocation */
  if (Size < sizeof(ds6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = DS6_UnitInit;
  Uni->Close = DS6_UnitClose;
  Uni->Response = DS6_UnitResponse;
  Uni->Render = DS6_UnitRender;
  return Uni;
}/* End of 'DS6_UnitRender' function */

/* END OF 'unit.c' FILE */
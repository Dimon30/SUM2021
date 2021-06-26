/* FILE NAME: u_cow.c
 * PROGRAMMER: DS6
 * DATE: 22.06.2021
 * PURPOSE: ???.
 */


#include "units.h"

typedef struct
{
  DS6_UNIT_BASE_FIELDS;
  ds6PRIMS Cow;
} ds6UNIT_COW;

/*
 * Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT_COW *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitInit( ds6UNIT_COW *Uni, ds6ANIM *Ani )
{
  DS6_RndPrimsLoad(&Uni->Cow, "BIN/MODELS/a.g3dm");

} /* End of 'DS6_UnitInit' function */

/*
 * Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT_COW *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitClose( ds6UNIT_COW *Uni, ds6ANIM *Ani )
{
  DS6_RndPrimsFree(&Uni->Cow);
} /* End of 'DS6_UnitClose' function */

/*
 * Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT_COW *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitResponse( ds6UNIT_COW *Uni, ds6ANIM *Ani )
{


} /* End of 'DS6_UnitResponse' function */

/*
 * Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *      ds6UNIT_COW *Uni;
 *  - animation context:
 *      ds6ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS6_UnitRender( ds6UNIT_COW *Uni, ds6ANIM *Ani )
{
  DS6_RndPrimsDraw(&Uni->Cow, MatrIdentity());
} /* End of 'DS6_UnitRender' function */

/*
 * Unit creation function.
 * ARGUMENTS: None.
 * RETURNS: 
     (ds6UNIT *) pointer to created unit.
*/
ds6UNIT * DS6_UnitCreateCow( VOID )
{
  ds6UNIT *Uni;

  if ((Uni = DS6_AnimUnitCreate(sizeof(ds6UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)DS6_UnitInit;
  Uni->Close = (VOID *)DS6_UnitClose;
  Uni->Response = (VOID *)DS6_UnitResponse;
  Uni->Render = (VOID *)DS6_UnitRender;
  return Uni;
}/* End of 'DS6_UnitCreateCow' function */

/* END OF 'u_cow.c' FILE */



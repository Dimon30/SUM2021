/* FILE NAME: ???
 * PROGRAMMER: DS6
 * DATE: 22.06.2021
 * PURPOSE: ???.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define DS6_MAX_UNITS 3000

#define DS6_UNIT_BASE_FIELDS \
  VOID (*Init)( ds6UNIT *Uni, ds6ANIM *Ani );      \
  VOID (*Close)( ds6UNIT *Uni, ds6ANIM *Ani );     \
  VOID (*Response)( ds6UNIT *Uni, ds6ANIM *Ani );  \
  VOID (*Render)( ds6UNIT *Uni, ds6ANIM *Ani )


typedef struct tagds6UNIT ds6UNIT;

typedef struct tagds6ANIM
{
  HWND hWnd;
  INT W, H;

  ds6UNIT *Units[DS6_MAX_UNITS];
  INT NumOfUnits;

  DBL 
    GlobalTime, GlobalDeltaTime,
    Time, DeltaTime,
    FPS;
  BOOL IsPause;

  BYTE Keys[256];
  BYTE KeysOld[256];
  BYTE KeysClick[256];

  INT Mx, My, Mz, Mdx, Mdy, Mdz;

  BYTE JBut[32], JButOld[32], JButClick[32];
  INT JPov;
  DBL JX, JY, JZ, JR;
} ds6ANIM;

struct tagds6UNIT
{
  DS6_UNIT_BASE_FIELDS;
  CamLoc
};

extern ds6ANIM DS6_Anim;
extern INT DS6_MouseWheel;

VOID DS6_AnimInit( HWND hWnd );
VOID DS6_AnimClose ( VOID );
VOID DS6_AnimResize(INT W, INT H );
VOID DS6_AnimCopyFrame( VOID );
VOID DS6_AnimRender( VOID );

/*
 * Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *      INT Size;
 * RETURNS: 
     (ds6UNIT *) pointer to created unit.
 */
ds6UNIT * DS6_AnimUnitCreate( INT Size );

VOID DS6_AnimUnitAdd( ds6UNIT *Uni );


VOID DS6_TimerInit( VOID );
VOID DS6_TimerResponse( VOID );


VOID DS6_AnimInputInit( VOID );
VOID DS6_AnimInputResponse( VOID );

#endif

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm")
#include <string.h>

#define MAX_UNITS 3000
typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

  BYTE Keys[256];
  BYTE KeysOld[256];
  BYTE KeysClick[256];
  INT Mx, My, Mz, Mdx, Mdy, Mdz;

  BYTE JBut[32], JButOld[32], JButClick[32];
  INT JPov;
  DBL JX, JY, JZ, JR;

UNIT *Units[MAX_UNITS];
INT NumOfUnits;

#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )

static VOID DS6_AnimKeyboardInit( VOID );
static VOID DS6_AnimKeyboardResponse( VOID );

static VOID DS6_AnimMousenit( VOID );
static VOID DS6_AnimMouseResponse( VOID );

static VOID DS6_AnimJoystickInit( VOID );
static VOID DS6_AnimJoysstickResponse( VOID );

VOID DS6_AnimInputInit( VOID );
VOID DS6_AnimInputResponse( VOID );

#define DS6_GETJOYSTIC_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## min) - 1)
#endif

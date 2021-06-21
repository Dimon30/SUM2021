#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define MAX_UNITS 3000
typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

UNIT *Units[MAX_UNITS];
INT NumOfUnits;

#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )

#endif
/*
 * FILENAME: timer.c
 * PRAGRAMMER: DS6
 * DATE: 16.06.2021
 * PURPOSE: Timer declaration module
 */

#ifndef __timer_h_
#define __timer_h_

#include <windows.h>

/* Global timer data */
extern DOUBLE 
  GLB_Time,       /* <-- totsl time per second */
  GLB_DeltaTime,  /* <-- interframe time per second */
  GLB_FPS;        /* <-- number frames per second */
extern BOOL GLB_IsPause;     /* <-- flag pause	additionally remind (in "tikach"-"klokach"): */

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );

#endif
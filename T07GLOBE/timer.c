/*
 * FILENAME: timer.c
 * PRAGRAMMER: DS6
 * DATE: 16.06.2021
 * PURPOSE: Timer implementation module
 */

#include <time.h>
#include "timer.h"

/* Global timer data */
DOUBLE 
  GLB_Time,       /* <-- totsl time per second */
  GLB_DeltaTime,  /* <-- interframe time per second */
  GLB_FPS;        /* <-- number frames per second */
BOOL GLB_IsPause;     /* <-- flag pause	additionally remind (in "tikach"-"klokach"): */
/* Local timer data */
static LONG StartTime,       /* <-- time of start progmam */
     OldTime,         /* <-- time of old frame */
     PauseTime,       /* <-- time of pause */
     OldFPSTime,      /* <-- time of old measure FPS */
     FrameCount;      /* <-- count of frame for FPS */
double SyncTime;  /* время в секундах с момента старта программы */

/* function - "timer" */
void Timer( void )
{
  long t = clock();
  static long StartTime = -1;

  if (StartTime == -1)
    StartTime = t;
  SyncTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
} /* End of 'Timer' function */

VOID GLB_TimerInit( VOID )
{  
  StartTime = OldTime = OldFPSTime = clock();
  FrameCount = 0;
  GLB_IsPause = FALSE;
}
VOID GLB_TimerResponse( VOID )  /* <-- updated timer */
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }
  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
}
/* END OF 'timer.c' FILE */
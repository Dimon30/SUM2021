/* FILE NAME: ???
 * PROGRAMMER: DS6
 * DATE: 22.06.2021
 * PURPOSE: ???.
 */
#include "anim.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

/* FILE NAME: timer.c
 * PROGRAMMER: DS6
 * DATE: 21.06.2021
 * PURPOSE: 3D math implementation module.
 */

VOID DS6_TimerInit( VOID )
{

  LARGE_INTEGER t;	

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  DS6_Anim.IsPause = FALSE;
  DS6_Anim.FPS = 30.0;
  PauseTime = 0;
}

VOID DS6_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  DS6_Anim.GlobalTime = (FLT)(t.QuadPart - StartTime) / TimePerSec;
  DS6_Anim.GlobalDeltaTime = (FLT)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (DS6_Anim.IsPause)
  {
    DS6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    DS6_Anim.DeltaTime = DS6_Anim.GlobalDeltaTime;
    DS6_Anim.Time = (FLT)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    DS6_Anim.FPS = FrameCounter * TimePerSec / (FLT)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
}

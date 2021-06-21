#include "timer.h"

/* FILE NAME: timer.c
 * PROGRAMMER: DS6
 * DATE: 21.06.2021
 * PURPOSE: 3D math implementation module.
 */

VOID TimerInit( VOID )
{

  LARGE_INTEGER t;	

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  IsPause = FALSE;
  FPS = 30.0;
  PauseTime = 0;
}
VOID TimerResponse( VOID )
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart – OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DBL)(t.QuadPart – PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart – OldTimeFPS > TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart – OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
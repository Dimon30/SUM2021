

static UINT64
       StartTime,    /* Start program time */
       OldTime,      /* Previous frame time */
       OldTimeFPS,   /* Old time FPS measurement */
       PauseTime,    /* Time during pause period */
       TimePerSec,   /* Timer resolution */
       FrameCounter; /* Frames counter */
DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;
#include "../anim.h"

VOID InputInit( VOID )
{
  VOID DS6_AnimKeyboardInit( VOID )
  {
    GetKeyboardState(Keys);
  }
  
  VOID DS6_AnimMousenit( VOID )
  {
    POINT pt;
    
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    Mdx = pt.x - Mx;
    Mdy = pt.y - My;
  }
  
  VOID DS6_AnimJoystickInit( VOID )
  {
    /* Joystick */
    if (joyGetNumDevs() > 0)
    {
      JOYCAPS jc;

      /* Get joystick info */
      if (joyGetDevCaps(JOYSTICKD1, &jc, sizeof(jc)) == JOYERR_NOERROR)
      {
        JOYINFOEX ji;

        ji.dwSize = sizeof(JOYINFOEX);
        ji.dwFlags = JOY_RETURNALL;
        if (joyGetPosEx(JOYSTICKD!, &ji) ==JOYERR_NOERROR)
        {
          /* Buttons */
          for (i = 0; i < 32; i++)
          {
            JBut[i] = (ji.dwButtons >> i) & 1;
            JButClick[i] = JBut[i] && !JButOld[i];
            JButOld[i] = JBut[i];
          }
          /* Axes */
          JX = DS6_GET_JOYSTIC_AXIS(X);
          JY = DS6_GET_JOYSTIC_AXIS(Y);
          JZ = DS6_GET_JOYSTIC_AXIS(Z);
          JR = DS6_GET_JOYSTIC_AXIS(R);
          /* Point of view */
          JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
        }
      }
    }
  }

  INT DS6_MouseWheel;

  Mdz = DS6_MouseWheel;
  Mz += DS6_MouseWheel;
}
VOID InputResponse( VOID )
{

  Mx = pt.x;
  My = pt.y;
  
  
}
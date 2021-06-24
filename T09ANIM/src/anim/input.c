/* FILE NAME: input.c
 * PROGRAMMER: DS6
 * DATE: 22.06.2021
 * PURPOSE: ???.
 */

#include <string.h>

#include "anim.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm")

#define DS6_GET_JOYSTIC_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## min) - 1)

INT DS6_MouseWheel;


static VOID DS6_AnimKeyboardInit( VOID )
{
  GetKeyboardState(DS6_Anim.Keys);
}
static VOID DS6_AnimKeyboardResponse( VOID )
{
  INT i;
  
  GetKeyboardState(DS6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    DS6_Anim.Keys[i] >>= 7;
    DS6_Anim.KeysClick[i] = DS6_Anim.Keys[i] && !DS6_Anim.KeysOld[i];
  }

  memcpy(DS6_Anim.KeysOld, DS6_Anim.Keys, 256);
}

static VOID DS6_AnimMouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(DS6_Anim.hWnd, &pt);

  DS6_Anim.Mdx = pt.x - DS6_Anim.Mx;
  DS6_Anim.Mdy = pt.y - DS6_Anim.My;
}
static VOID DS6_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(DS6_Anim.hWnd, &pt);

  DS6_Anim.Mx = pt.x;
  DS6_Anim.My = pt.y;
  DS6_Anim.Mdz = DS6_MouseWheel;
  DS6_Anim.Mz += DS6_MouseWheel;
}

static VOID DS6_AnimJoystickInit( VOID )
{
  INT i;

  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
    {
      JOYINFOEX ji;

      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
        {
          DS6_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
          DS6_Anim.JButClick[i] = DS6_Anim.JBut[i] && !DS6_Anim.JButOld[i];
          DS6_Anim.JButOld[i] = DS6_Anim.JBut[i];
        }
        /* Axes */
        DS6_Anim.JX = DS6_GET_JOYSTIC_AXIS(X);
        DS6_Anim.JY = DS6_GET_JOYSTIC_AXIS(Y);
        DS6_Anim.JZ = DS6_GET_JOYSTIC_AXIS(Z);
        DS6_Anim.JR = DS6_GET_JOYSTIC_AXIS(R);
        /* Point of view */
        DS6_Anim.JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
      }
    }
  }
}
static VOID DS6_AnimJoysstickResponse( VOID )
{
  
}


VOID DS6_AnimInputInit( VOID )
{
  VOID DS6_AnimKeyboardInit( VOID );
  VOID DS6_AnimMouseInit( VOID );
}
VOID DS6_AnimInputResponse( VOID )
{
  VOID DS6_AnimKeyboardResponse( VOID );
  VOID DS6_AnimMouseResponse( VOID );
}
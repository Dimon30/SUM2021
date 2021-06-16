/*
 * FILENAME: globe.c
 * PRAGRAMMER: DS6
 * DATE: 14.06.2021
 * PURPOSE:
 */
#include <windows.h>
#include <math.h>
#include <time.h>

#include "globe.h"


#define GRID_W 25
#define GRID_H 18
#define pi 3.14159265358979323846

static VEC Geom[GRID_H][GRID_W];

/* Current work space */
static INT WinW, WinH;

VEC RotateZ( VEC V, DBL Angle )
{
  DBL a = Angle * pi / 180, s = sin(a), c = cos(a);
  VEC r;

  r.X = V.X * c - V.Y * s;
  r.Y = V.X * s + V.Y * c;
  r.Z = V.Z;
  return r;
}

VEC RotateY( VEC V, DBL Angle )
{
  DBL a = Angle * pi / 180, s = sin(a), c = cos(a);
  VEC r;

  r.Z = V.Z * c - V.X * s;
  r.X = V.Z * s + V.X * c;
  r.Y = V.Y;
  return r;
}
VEC RotateX( VEC V, DBL Angle )
{
  DBL a = Angle * pi / 180, s = sin(a), c = cos(a);
  VEC r;

  r.Y = V.Y * c - V.Z * s;
  r.Z = V.Y * s + V.Z * c;
  r.X = V.X;
  return r;
}

VOID GlobeSet( INT w, INT h, DBL R)
{
  INT i, j;
  DBL theta, phi;
  WinW = w;
  WinH = h;

  for (i = 0, theta = 0; i < GRID_H; i++, theta += pi / (GRID_H - 1))
    for (j = 0, phi = 0; j < GRID_W; j++, phi += 2 * pi / (GRID_W - 1))
    {
      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}
VOID GlobeDraw( HDC hDC )
{
  INT s = 2, i, j, r, k;
  DBL t = GLB_Time;

  static POINT pnts[GRID_H][GRID_W];
  r = WinW < WinH ? WinW : WinH;

  /* Project all points to screen */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      VEC p = Geom[i][j];

      p = RotateY(p, -15 * t);
      p = RotateZ(p, -23.66);
      p = RotateX(p, -12);

      pnts[i][j].x = WinW / 2 + p.X * r * 0.46;
      pnts[i][j].y = WinH / 2 - p.Y * r * 0.46;
    }
#if 0
    for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s, pnts[i][j].x + s, pnts[i][j].y + s);
    }
  for (j = 0; j < GRID_W - 1; j ++)
    {
      MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
      for (i = 0; i < GRID_H - 1; i++)
        LineTo(hDC, pnts[i + 1][j].x, pnts[i + 1][j].y);
    }
  for (i = 0; i < GRID_H - 1; i ++)
    {
       MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
       for (j = 0; j < GRID_W - 1; j++)
         LineTo(hDC, pnts[i + 1][j].x, pnts[i + 1][j].y);
    }
#endif

  for (k = 1; k < 2; k++)
  {
    if (k == 0)
    {
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCPenColor(hDC, RGB(200, 0, 0));
      //SetDCBrushColor(hDC, RGB(255, 255, 255));
    }
    else
    {
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(NULL_BRUSH));
      SetDCPenColor(hDC, RGB(255, 0, 0));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
    }
  
  for (i = 0; i < GRID_H - 1; i++)
    for (j = 0; j < GRID_W - 1; j++)
    {
      POINT pts[4];
      INT kaef;

      pts[0] = pnts[i][j];
      pts[1] = pnts[i][j + 1];
      pts[2] = pnts[i + 1][j + 1];
      pts[3] = pnts[i + 1][j];

      kaef = (pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
          (pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
          (pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
          (pts[0].x - pts[1].x) * (pts[0].y + pts[1].y);
      if (kaef >= 0 && k == 0 ||  kaef < 0 && k == 1)
        continue;

      Polygon(hDC, pts, 4);
    }
  }
}
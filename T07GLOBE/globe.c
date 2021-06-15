/*
 * FILENAME: T07GLOBE
 * PRAGRAMMER: DS6
 * DATE: 14.06.2021
 * PURPOSE:
 */
/* #include <windows.h> */
#include <math.h>

#include "globe.h"


#define GRID_W 15
#define GRID_H 9

static VEC Geom[GRID_H][GRID_W];

/* Current work space */
static INT WinW, WinH;

VOID GlobeSet( INT w, INT h, DBL R)
{
  INT i, j;
  DBL pi = 3.14159265358979323846, theta, phi;
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
  INT s = 2, i, j, r;
  static POINT pnts[GRID_H][GRID_W];
  r = WinW < WinH ? WinW : WinH;

  /* Project all points to screen */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      pnts[i][j].x = WinW / 2 + Geom[i][j].X * r * 0.46;
      pnts[i][j].y = WinH / 2 - Geom[i][j].Y * r * 0.46;
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
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; ++)
    {
      Polygon(hDC, pts, 4;

      pts[0] = pnts[i][j];
      pts[1] = pnts[i][j + 1];
      pts[2] = pnts[i + 1][j + 1];
      pts[3] = pnts[i + 1][j];
      if ((pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
           pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
           pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) +
           pts[0].x - pts[1].x) * (pts[0].y + pts[1].y)) > 0)
        continue;
    }
}
/*
 * FILENAME: T07GLOBE
 * PRAGRAMMER: DS6
 * DATE: 14.06.2021
 * PURPOSE:
 */
#include <math.h>
#include "globe.h"

VOID GlobeSet(INT WinH, WinW, )
{
  INT i, j, GRID_H, GRID_W;
  DOUBLE pi = 3.14159265358979323846, theta, phi;
  for (i = 0, theta = 0; i < GRID_H; i++, theta += pi / (GRID_H - 1))
    for (j = 0, phi = 0; j < GRID_W; j++, phi += 2 * pi / (GRID_W - 1))
    {
      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
}
VOID GlobeDraw(HDC hDC)
{
  static POINT pnts
}
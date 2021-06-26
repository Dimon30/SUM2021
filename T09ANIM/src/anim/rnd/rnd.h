/* FILE NAME: main.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
/* Shaders stock maximum size */
#include <glew.h>

#include "../../def.h"

#include "res/rndres.h"

extern HWND DS6_hRndWnd;                  /* Work window handle */
extern HDC DS6_hRndDC;                    /* Work window memory device context */
extern HGLRC DS6_hRndGLRC;                /* OpenGL rendering context */
extern INT DS6_RndFrameW, DS6_RndFrameH;  /* Work window size */

extern FLT
  DS6_RndProjSize,     /* Project plane fit square */
  DS6_RndProjDist ,    /* Distance to project plane from viewer (near) */
  DS6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  DS6_RndMatrView, /* View coordinate system matrix */
  DS6_RndMatrProj, /* Projection coordinate system matrix */
  DS6_RndMatrVP;   /* Stored (View * Proj) matrix */

extern VEC DS6_RndCamLoc;

VOID DS6_RndInit( HWND hWnd );

VOID DS6_RndClose( VOID );

VOID DS6_RndProjSet( VOID );

VOID DS6_RndResize( INT W, INT H );

VOID DS6_RndStart( VOID );

VOID DS6_RndEnd( VOID );

VOID DS6_RndCopyFrame( VOID );

VOID DS6_RndCamSet( VEC Loc, VEC At, VEC Up1 );

typedef struct tagds6VERTEX
{
  VEC P; /* Vertex position */
  VEC2 T;
  VEC N;
  VEC4 C;

} ds6VERTEX;

typedef struct tagds6PRIM
{
  MATR Trans;
  INT VBuf;
  INT VA;
  INT IBuf;
  INT NumOfElements;
  INT MtlNo;
} ds6PRIM;
/* Primitive type */
typedef enum tagds6PRIM_TYPE
{
  DS6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  DS6_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  DS6_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  DS6_RND_PRIM_POINTS,   /* Arrauy of points */
} ds6PRIM_TYPE;

/*
VEC4 Vec4Set( FLT A, FLT B, FLT C, FLT D );
VEC4 Vec4Set1( FLT A );
VEC2 Vec2Set( FLT A, FLT B );
VEC2 Vec2Set1( FLT A );
*/

VOID DS6_RndPrimCreate( ds6PRIM *Pr, ds6PRIM_TYPE Type, ds6VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

VOID DS6_RndPrimFree( ds6PRIM *Pr );

VOID DS6_RndPrimDraw( ds6PRIM *Pr, MATR World );

BOOL DS6_RndPrimLoad( ds6PRIM *Pr, CHAR *FileName );

//BOOL DS6_RndPrimCreateGrid( ds6PRIM *Pr, INT SplitW, INT SplitH);

//BOOL DS6_RndPrimCreateSphere( ds6PRIM *Pr, VEC C, FLT R, INT SplitW, INT SplitH );

//BOOL DS6_RndPrimCreatePlane( ds6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH);


/***
 * Primitive collection support
 ***/

/* Primitive collection data type */
typedef struct tagds6PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  ds6PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} ds6PRIMS;

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       ds6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL DS6_RndPrimsCreate( ds6PRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       ds6PRIMS *Prs;
 * RETURNS: None.
 */
VOID DS6_RndPrimsFree( ds6PRIMS *Prs );

/*
 * Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       ds6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID DS6_RndPrimsDraw( ds6PRIMS *Prs, MATR World );

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       ds6PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL DS6_RndPrimsLoad( ds6PRIMS *Prs, CHAR *FileName );

#endif /* __rnd_h_*/

/* END OF 'rnd.h' FILE */
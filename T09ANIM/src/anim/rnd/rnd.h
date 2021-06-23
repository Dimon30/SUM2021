/* FILE NAME: main.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */
#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
/* Shaders stock maximum size */
#define DS6_MAX_SHADERS 30
#include <glew.h>

#include "../../def.h"

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
} ds6PRIM;

typedef struct tagds6SHADER
{
  CHAR Name[DS6_MAX_SHADERS];
  INT ProgId;
} ds6SHADER;

/* Shadre stock array and it size */
ds6SHADER DS6_RndShaders[DS6_MAX_SHADERS];
INT DS6_RndShadersSize;

VEC4 Vec4Set( FLT A, FLT B, FLT C, FLT D );
VEC4 Vec4Set1( FLT A );
VEC2 Vec2Set( FLT A, FLT B );
VEC2 Vec2Set1( FLT A );

VOID DS6_RndPrimCreate( ds6PRIM *Pr, ds6VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

VOID DS6_RndPrimFree( ds6PRIM *Pr );

VOID DS6_RndPrimDraw( ds6PRIM *Pr, MATR World );

BOOL DS6_RndPrimLoad( ds6PRIM *Pr, CHAR *FileName );

//BOOL DS6_RndPrimCreateGrid( ds6PRIM *Pr, INT SplitW, INT SplitH);

//BOOL DS6_RndPrimCreateSphere( ds6PRIM *Pr, VEC C, FLT R, INT SplitW, INT SplitH );

//BOOL DS6_RndPrimCreatePlane( ds6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH);

VOID DS6_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text );

CHAR * DS6_RndLoadTextFromFile( CHAR *FileName );

INT DS6_RndShdLoad( CHAR *FileNamePrefix );

VOID DS6_RndShdFree( INT ProgId );

VOID DS6_RndShadersInit( VOID );

VOID DS6_RndShadersClose( VOID );

INT DS6_RndShaderAdd( CHAR *FileNamePrefix );

VOID DS6_RndShadersUpdate( VOID );



#endif /* __rnd_h_*/

/* END OF 'rnd.h' FILE */
/* FILE NAME: rndbase.c
 * PROGRAMMER: DS6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation start up module.
 */

#include "../anim.h"
#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")


VOID DS6_hRndCamSet( VEC Loc, VEC At, VEC Up1 )
{
  DS6_RndMatrView = MatrView(Loc, At, Up1);
  DS6_RndMatrVP = MatrMulMatr(DS6_RndMatrView, DS6_RndMatrProj);
}

VOID DS6_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  DS6_hRndWnd = hWnd;
  DS6_hRndDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(DS6_hRndDC, &pfd);
  DescribePixelFormat(DS6_hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(DS6_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  DS6_hRndGLRC = wglCreateContext(DS6_hRndDC);
  wglMakeCurrent(DS6_hRndDC, DS6_hRndGLRC);

  /* Initializing GLEW library */
  if (glewInit() != GLEW_OK)
  {
    MessageBox(DS6_hRndWnd, "Error extensions initializing", "Error",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(DS6_hRndWnd, "Error: no shaders support", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(DS6_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(DS6_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(DS6_hRndGLRC);

  DS6_hRndGLRC = hRC;
  wglMakeCurrent(DS6_hRndDC, DS6_hRndGLRC);
  /* Set default OpenGL parameters */
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.30f, 0.47f, 0.8, 1);
  DS6_RndShadersInit();

  DS6_RndProjSize = 0.1,
  DS6_RndProjDist = 0.1,
  DS6_RndProjFarClip = 300;

  DS6_RndFrameW = 47;
  DS6_RndFrameH = 47;
  DS6_hRndCamSet(VecSet(5, 5, 50), VecSet(0, 0, 0), VecSet(0, 1, 0));
}

VOID DS6_RndClose( VOID )
{
  DS6_RndShadersClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(DS6_hRndGLRC);
  ReleaseDC(DS6_hRndWnd, DS6_hRndDC);
}

VOID DS6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* save size */
  DS6_RndFrameW = W;
  DS6_RndFrameH = H;

  /* recalculate projection */
  DS6_RndProjSet();
}

VOID DS6_RndCopyFrame( VOID )
{
  /// SwapBuffers(DS6_Anim.hDC);
  wglSwapLayerBuffers(DS6_hRndDC, WGL_SWAP_MAIN_PLANE);
}

VOID DS6_RndStart( VOID )
{
  static DBL load = 0;

  if ((load += DS6_Anim.GlobalDeltaTime) > 1)
  {
    load = 0;
    DS6_RndShadersUpdate();
  }
  /* Clear frame */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

VOID DS6_RndEnd( VOID )
{
  glFinish();
}

VOID DS6_RndProjSet( VOID )
{
  FLT rx, ry;

  rx = ry = DS6_RndProjSize / 2;
  if (DS6_RndFrameW > DS6_RndFrameH)
    rx *= (FLT)DS6_RndFrameW / DS6_RndFrameH;
  else
    ry *= (FLT)DS6_RndFrameH / DS6_RndFrameW;
  DS6_RndMatrProj = 
    MatrFrustum(-rx, rx, -ry, ry, DS6_RndProjDist, DS6_RndProjFarClip);
  DS6_RndMatrVP = MatrMulMatr(DS6_RndMatrView, DS6_RndMatrProj);
}
/* END OF 'rndbase.c' FILE */
#include "../../anim.h"

#define DS6_STR_MAX  300

typedef struct tagds6SHADER
{
  CHAR Name[DS6_STR_MAX];
  INT ProgId;
} ds6SHADER;

#define DS6_MAX_TEXTURES 300

/* Texture representation type */
typedef struct tagds6TEXTURE
{
  CHAR Name[DS6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} ds6TEXTURE;

#define DS6_MAX_SHADERS  47
#define DS6_MAX_MATERIALS 300

typedef struct tagds6MATERIAL
{
  CHAR Name[DS6_STR_MAX]; /* Material name */


  /* Illumination coefficients */    
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */

  FLT Trans;                /* Transparency factor */
  INT Tex[8];               /* Texture references from texture table (or -1) */

  INT ShdNo;                /* Shader number in shader table */
} ds6MATERIAL;


  VOID DS6_RndResInit( VOID );
  VOID DS6_RndResClose( VOID );
  ds6SHADER DS6_RndShaders[DS6_MAX_SHADERS];
  INT DS6_RndShadersSize;

  INT DS6_RndShaderAdd( CHAR *FileNamePrefix );
  VOID DS6_RndShadersUpdate( VOID );
  VOID RndShdFree( INT ShdNo );
  VOID DS6_RndShadersInit( VOID );
  VOID DS6_RndShadersClose( VOID );

  ds6TEXTURE DS6_RndTextures[DS6_MAX_TEXTURES]; /* Array of textures */
  INT DS6_RndTexturesSize;                    /* Textures array store size */

  INT DS6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
  INT DS6_RndTexAdd( CHAR *FileName );

  VOID DS6_RndTextureDelete( INT TexNo );
  DS6_RndTexInit( VOID );
  DS6_RndTexClose( VOID );

  /* Material stock */
  ds6MATERIAL DS6_RndMaterials[DS6_MAX_MATERIALS]; /* Array of materials */
  INT DS6_RndMaterialsSize;                        /* Materials array store size */

  INT DS6_RndMtllAdd( ds6MATERIAL *Mtl ); 
  INT DS6_RndMtlApply( INT MtlNo );
  VOID DS6_RndMtlInit( VOID );
  VOID DS6_RndMtlClose( VOID );
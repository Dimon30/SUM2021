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

/* Draw array of primitives function.
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
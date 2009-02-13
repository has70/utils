/*------------------------------------------------------------------------------
    SCEngine - A 3D real time rendering engine written in the C language
    Copyright (C) 2006-2009  Antony Martin <martin(dot)antony(at)yahoo(dot)fr>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -----------------------------------------------------------------------------*/
 
/* created: 02/11/2008 */

#ifndef SCELEVELOFDETAIL_H
#define SCELEVELOFDETAIL_H

#include <SCE/utils/SCEMatrix.h>
#include <SCE/interface/SCEBoundingBox.h>
#include <SCE/interface/SCECamera.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (*SCE_FGetLODFunc)(float);

typedef struct sce_slevelofdetail SCE_SLevelOfDetail;
struct sce_slevelofdetail
{
    int lod;                    /**< LOD level */
    int minlod, maxlod;         /**< Minimum & maximum values for \c lod */
    SCE_SBoundingBox *box;      /**< Bounding box of the entity */
    float size;                 /**< Size of the entity's bounding box */
    float dist;                 /**< Distance between the entity & the camera */
    SCE_FGetLODFunc getlod;     /**< Get LOD from the size */
};

void SCE_Lod_Init (SCE_SLevelOfDetail*);

SCE_SLevelOfDetail* SCE_Lod_Create (void);
void SCE_Lod_Delete (SCE_SLevelOfDetail*);

void SCE_Lod_SetBoundingBox (SCE_SLevelOfDetail*, SCE_SBoundingBox*);
void SCE_Lod_SetGetLODFunc (SCE_SLevelOfDetail*, SCE_FGetLODFunc);

SCE_SBoundingBox* SCE_Lod_GetBoundingBox (SCE_SLevelOfDetail*);

int SCE_Lod_Compute (SCE_SLevelOfDetail*, SCE_TMatrix4, SCE_SCamera*);

int SCE_Lod_GetLOD (SCE_SLevelOfDetail*);
float SCE_Lod_GetSize (SCE_SLevelOfDetail*);
float SCE_Lod_GetDistance (SCE_SLevelOfDetail*);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* guard */

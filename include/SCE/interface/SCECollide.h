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
 
/* created: 08/01/2009
   updated: 16/06/2009 */

#ifndef SCECOLLIDE_H
#define SCECOLLIDE_H

#include <SCE/utils/SCERectangle.h>
#include <SCE/utils/SCEPlane.h>
#include <SCE/interface/SCEBoundingBox.h>
#include <SCE/interface/SCEBoundingSphere.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SCE_COLLIDE_OUT 0
#define SCE_COLLIDE_IN 1
#define SCE_COLLIDE_PARTIALLY 2

int SCE_Collide_PlanesWithPoint (SCE_SPlane*, unsigned int, float, float,float);
int SCE_Collide_PlanesWithPointv (SCE_SPlane*, unsigned int, SCE_TVector3);

int SCE_Collide_PlanesWithBB (SCE_SPlane*, unsigned int, SCE_SBoundingBox*);
int SCE_Collide_PlanesWithBBBool (SCE_SPlane*, unsigned int, SCE_SBoundingBox*);
int SCE_Collide_PlanesWithBS (SCE_SPlane*, unsigned int, SCE_SBoundingSphere*);
int SCE_Collide_PlanesWithBSBool (SCE_SPlane*, unsigned int,
                                  SCE_SBoundingSphere*);

int SCE_Collide_RectWithBS (SCE_SFloatRect*, SCE_SBoundingSphere*);

int SCE_Collide_AABBWithPoint (SCE_SBoundingBox*, float, float, float);
int SCE_Collide_AABBWithPointv (SCE_SBoundingBox*, SCE_TVector3);
int SCE_Collide_AABBWithBS (SCE_SBoundingBox*, SCE_SBoundingSphere*);
int SCE_Collide_AABBWithBSBool (SCE_SBoundingBox*, SCE_SBoundingSphere*);

int SCE_Collide_BBWithPoint (SCE_SBoundingBox*, float, float, float);
int SCE_Collide_BBWithPointv (SCE_SBoundingBox*, SCE_TVector3);
int SCE_Collide_BBWithBS (SCE_SBoundingBox*, SCE_SBoundingSphere*);
int SCE_Collide_BBWithBB (SCE_SBoundingBox*, SCE_SBoundingBox*);

int SCE_Collide_BSWithPoint (SCE_SBoundingSphere*, float, float, float);
int SCE_Collide_BSWithPointv (SCE_SBoundingSphere*, SCE_TVector3);
int SCE_Collide_BSWithBB (SCE_SBoundingSphere*, SCE_SBoundingBox*);
int SCE_Collide_BSWithBS (SCE_SBoundingSphere*, SCE_SBoundingSphere*);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* guard */

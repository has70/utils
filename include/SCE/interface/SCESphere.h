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

/* created: 04/08/2009
   updated: 04/08/2009 */

#ifndef SCESPHERE_H
#define SCESPHERE_H

#include <SCE/utils/SCEVector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sce_ssphere SCE_SSphere;
struct sce_ssphere {
    SCE_TVector3 center;
    float radius;
};

void SCE_Sphere_Copy (SCE_SSphere*, const SCE_SSphere*);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* guard */
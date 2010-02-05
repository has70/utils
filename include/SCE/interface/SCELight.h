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
 
/* created: 13/03/2008
   updated: 15/03/2009 */

#ifndef SCELIGHT_H
#define SCELIGHT_H

#include <SCE/core/SCECLight.h>
#include <SCE/interface/SCEBoundingSphere.h>
#include <SCE/interface/SCENode.h>
#include <SCE/interface/SCEShaders.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \copydoc sce_slight */
typedef struct sce_slight SCE_SLight;
/**
 * \brief A light! (omg)
 */
struct sce_slight
{
    SCE_CLight *clight; /* lumiere coeur */
    float intensity;    /* coefficient d'intensite */
    float radius;       /* rayon de portee de la lumiere */
    int activated;      /* defini si la lumiere est active */
    SCE_SBoundingSphere sphere; /**< Bounding sphere (if is omnidirectionnal) */
    SCE_SNode *node;    /* noeud de la lumiere */
};

void SCE_Light_Init (SCE_SLight*);

/* cree une lumiere */
SCE_SLight* SCE_Light_Create (void);
void SCE_Light_Delete (SCE_SLight*);

void SCE_Light_Activate (SCE_SLight*, int);
int SCE_Light_IsActivated (SCE_SLight*);

SCE_SNode* SCE_Light_GetNode (SCE_SLight*);

void SCE_Light_SetColor (SCE_SLight*, float, float, float);
void SCE_Light_SetColorv (SCE_SLight*, float*);
float* SCE_Light_GetColor (SCE_SLight*);
void SCE_Light_GetColorv (SCE_SLight*, float*);

void SCE_Light_GetPositionv (SCE_SLight*, float*);

void SCE_Light_GetDirectionv (SCE_SLight*, float*);

void SCE_Light_Infinite (SCE_SLight*, int);
int SCE_Light_IsInfinite (SCE_SLight*);

void SCE_Light_SetAngle (SCE_SLight*, float);
float SCE_Light_GetAngle (SCE_SLight*);

void SCE_Light_SetIntensity (SCE_SLight*, float);
float SCE_Light_GetIntensity (SCE_SLight*);

void SCE_Light_SetRadius (SCE_SLight*, float);
float SCE_Light_GetRadius (SCE_SLight*);

void SCE_Light_ActivateLighting (int);

void SCE_Light_Use (SCE_SLight*);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* guard */

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
 
/* created: 24/03/2008
   updated: 12/11/2008 */

#include <SCE/SCEMinimal.h>

#include <SCE/core/SCECPointSprite.h>

#if 0
/* tampon d'un simple point */
static SCE_CVertexBuffer *vb = NULL;
static SCE_TVector3 pos = {0., 0., 0.};

/* ajoute le 24/03/2008 */
int SCE_CPointSpriteInit (void)
{
    SCE_CVertexDeclaration dec;
    SCE_btstart ();
#define SCE_POINTASSERT(c)\
    if (c)\
    {\
        SCE_CDeleteVertexBuffer (vb);\
        SCEE_LogSrc ();\
        SCE_btend ();\
        return SCE_ERROR;\
    }
    SCE_POINTASSERT (!(vb = SCE_CCreateVertexBuffer ()))
    SCE_POINTASSERT (SCE_CAddVertexBufferData (vb, 3 * sizeof *pos, pos) < 0)
    SCE_POINTASSERT (SCE_CAddVertexDeclaration (vb, &dec) < 0)
    SCE_CInitVertexDeclaration (&dec);
    dec.attrib = SCE_POSITION;
    dec.type = SCE_FLOAT;
    dec.size = 3;
    dec.active = SCE_TRUE;
    SCE_CBuildVertexBuffer (vb, GL_STREAM_DRAW);
    return SCE_OK;
}
#endif

void SCE_CInitPointSprite (SCE_CPointSprite *point)
{
    point->size = 1.0f;
    point->smooth = SCE_FALSE;
    point->textured = SCE_FALSE;
    point->att[0] = 1.0f;
    point->att[1] = point->att[2] = 0.0f;
    point->minsize = 1.0f;
    point->maxsize = 64.0f;     /* TODO: check the limit */
}

SCE_CPointSprite* SCE_CCreatePointSprite (void)
{
    SCE_CPointSprite *point = NULL;
    SCE_btstart ();
    if (!(point = SCE_malloc (sizeof *point)))
        SCEE_LogSrc ();
    else
        SCE_CInitPointSprite (point);
    SCE_btend ();
    return point;
}

void SCE_CDeletePointSprite (SCE_CPointSprite *point)
{
    SCE_free (point);
}


void SCE_CSetPointSpriteSize (SCE_CPointSprite *point, float size)
{
    point->size = size;
}
float SCE_CGetPointSpriteSize (SCE_CPointSprite *point)
{
    return point->size;
}

void SCE_CSmoothPointSprite (SCE_CPointSprite *point, int smooth)
{
    point->smooth = smooth;
}
int SCE_CIsPointSpriteSmoothed (SCE_CPointSprite *point)
{
    return point->smooth;
}

void SCE_CActivatePointSpriteTexture (SCE_CPointSprite *point, int activated)
{
    point->textured = activated;
}
void SCE_CEnablePointSpriteTexture (SCE_CPointSprite *point)
{
    point->textured = SCE_TRUE;
}
void SCE_CDisablePointSpriteTexture (SCE_CPointSprite *point)
{
    point->textured = SCE_FALSE;
}

void SCE_CSetPointSpriteAttenuations (SCE_CPointSprite *point,
                                      float a, float b, float c)
{
    point->att[0] = a; point->att[1] = b; point->att[2] = c;
}
void SCE_CSetPointSpriteAttenuationsv (SCE_CPointSprite *point, SCE_TVector3 at)
{
    memcpy (point->att, at, 3 * sizeof *point->att);
}


void SCE_CUsePointSprite (SCE_CPointSprite *point)
{
    if (point)
    {
        glPointSize (point->size); 
        /* TODO: manage ARB_point_parameters extensions :
           GL_ARB_point_parameters, GL_ARB_point_sprite,
           GL_EXT_point_parameters */
        glPointParameterfv (GL_POINT_DISTANCE_ATTENUATION, point->att);
        glPointParameterf (GL_POINT_SIZE_MAX, point->maxsize);
        glPointParameterf (GL_POINT_SIZE_MIN, point->minsize);

        if (point->smooth)
            glEnable (GL_POINT_SMOOTH);
        if (point->textured)
        {
            /* exige que la texture ait deja ete appliquee */
            glTexEnvf (GL_POINT_SPRITE, GL_COORD_REPLACE, SCE_TRUE);
            glEnable (GL_POINT_SPRITE);
        }
    }
    else
    {
        glTexEnvf (GL_POINT_SPRITE, GL_COORD_REPLACE, SCE_FALSE);
        glDisable (GL_POINT_SPRITE);
        glDisable (GL_POINT_SMOOTH);
    }
}

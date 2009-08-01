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
 
/* created: 29/07/2009
   updated: 01/08/2009 */

#include <SCE/SCEMinimal.h>

#include <SCE/core/SCECVertexBuffer.h>

#define SCE_BUFFER_OFFSET(p) ((char*)NULL + (p))

static SCE_CVertexBuffer *vb_bound = NULL;
static SCE_CIndexBuffer *ib_bound = NULL;

void SCE_CInitVertexBufferData (SCE_CVertexBufferData *data)
{
    SCE_CInitBufferData (&data->data);
    SCE_CInitVertexArray (&data->va);
    SCE_List_InitIt (&data->it);
    SCE_List_SetData (&data->it, data);
    data->vb = NULL;
}
SCE_CVertexBufferData* SCE_CCreateVertexBufferData (void)
{
    SCE_CVertexBufferData *data = NULL;
    if (!(data = SCE_malloc (sizeof *data)))
        SCEE_LogSrc ();
    else
        SCE_CInitVertexBufferData (data);
    return data;
}
void SCE_CClearVertexBufferData (SCE_CVertexBufferData *data)
{
    SCE_CRemoveVertexBufferData (data);
    SCE_CClearVertexArray (&data->va);
    SCE_CClearBufferData (&data->data);
}
void SCE_CDeleteVertexBufferData (SCE_CVertexBufferData *data)
{
    if (data) {
        SCE_CClearVertexBufferData (data);
        SCE_free (data);
    }
}

void SCE_CInitVertexBuffer (SCE_CVertexBuffer *vb)
{
    SCE_CInitBuffer (&vb->buf);
    SCE_List_Init (&vb->data);
    SCE_List_SetFreeFunc (&vb->data, NULL);
    vb->n_vertices = 0;
}
SCE_CVertexBuffer* SCE_CCreateVertexBuffer (void)
{
    SCE_CVertexBuffer *vb = NULL;
    if (!(vb = SCE_malloc (sizeof *vb)))
        SCEE_LogSrc ();
    else
        SCE_CInitVertexBuffer (vb);
    return vb;
}
void SCE_CClearVertexBuffer (SCE_CVertexBuffer *vb)
{
    SCE_List_Clear (&vb->data);
    SCE_CClearBuffer (&vb->buf);
}
void SCE_CDeleteVertexBuffer (SCE_CVertexBuffer *vb)
{
    if (vb) {
        SCE_CClearVertexBuffer (vb);
        SCE_free (vb);
    }
}

void SCE_CInitIndexBuffer (SCE_CIndexBuffer *ib)
{
    SCE_CInitBuffer (&ib->buf);
    SCE_CInitBufferData (&ib->data);
    SCE_CAddBufferData (&ib->buf, &ib->data);
    SCE_CInitIndexArray (&ib->ia);
    ib->ia.data = SCE_BUFFER_OFFSET (0);
    ib->n_indices = 0;
}
SCE_CIndexBuffer* SCE_CCreateIndexBuffer (void)
{
    SCE_CIndexBuffer *ib = NULL;
    if (!(ib = SCE_malloc (sizeof *ib)))
        SCEE_LogSrc ();
    else
        SCE_CInitIndexBuffer (ib);
    return ib;
}
void SCE_CClearIndexBuffer (SCE_CIndexBuffer *ib)
{
    SCE_CClearBufferData (&ib->data);
    SCE_CClearBuffer (&ib->buf);
}
void SCE_CDeleteIndexBuffer (SCE_CIndexBuffer *ib)
{
    if (ib) {
        SCE_CClearIndexBuffer (ib);
        SCE_free (ib);
    }
}


/**
 * \brief Specifies the array data of a vertex buffer data
 *
 * The structure \p data is given to the vertex array of \p vbd
 * calling SCE_CSetVertexArrayData().
 * \sa SCE_CSetVertexArrayData(), SCE_CAddVertexBufferData
 */
void SCE_CSetVertexBufferDataArrayData (SCE_CVertexBufferData *vbd,
                                        SCE_CVertexArrayData *data,
                                        unsigned int n_vertices)
{
    vbd->data.data = data->data;
    vbd->data.size = SCE_CSizeof (data->type) * data->size * n_vertices;
    SCE_CSetVertexArrayData (&vbd->va, data);
}
/**
 * \brief Set modified vertices range
 * \param range range of modified vertices, [0] is the first modified vertex
 * and [1] the number of modified vertices
 * \sa SCE_CModifiedBufferData()
 */
void SCE_CModifiedVertexBufferData (SCE_CVertexBufferData *vbd, size_t *range)
{
    size_t r[2];
    SCE_CVertexArrayData *d = SCE_CGetVertexArrayData (&vbd->va);
    r[0] = r[1] = d->size * SCE_CSizeof (d->type);
    r[0] *= range[0];
    r[1] *= range[1];
    SCE_CModifiedBufferData (&vbd->data, r);
}
/**
 * \brief Enables the given vertex buffer data for the render
 * \sa SCE_CSetVertexBufferRenderMode()
 */
void SCE_CEnableVertexBufferData (SCE_CVertexBufferData *vbd)
{
    SCE_List_Appendl (&vbd->vb->data, &vbd->it);
}
/**
 * \brief Disables the given vertex buffer data for the render
 * \sa SCE_CSetVertexBufferRenderMode()
 */
void SCE_CDisableVertexBufferData (SCE_CVertexBufferData *vbd)
{
    SCE_List_Removel (&vbd->it);
}


/**
 * \brief Gets the buffer of a vertex buffer
 */
SCE_CBuffer* SCE_CGetVertexBufferBuffer (SCE_CVertexBuffer *vb)
{
    return &vb->buf;
}

/**
 * \brief Adds data to a vertex buffer
 *
 * The memory of \p d is never freed by module CVertexBuffer.
 * \sa SCE_CSetVertexBufferDataArrayData(), SCE_CAddBufferData()
 */
void SCE_CAddVertexBufferData (SCE_CVertexBuffer *vb, SCE_CVertexBufferData *d)
{
    SCE_CAddBufferData (&vb->buf, &d->data);
    SCE_List_Appendl (&vb->data, &d->it);
    d->vb = vb;
}
/**
 * \deprecated
 * \todo useless, unlogical: better to manage a CVertexBufferData structure
 * at this level, and use
 * \brief Adds a new vertex buffer data from vertex array data
 * \param data vertex buffer data will be build around these data
 * \param n_vertices number of vertices in \p data
 *
 * Deprecated function, better to use SCE_CAddVertexBufferData() and
 * SCE_CSetVertexBufferDataArrayData().
 * \sa SCE_CSetVertexBufferDataArrayData(), SCE_CAddVertexBufferData()
 */
SCE_CVertexBufferData* SCE_CAddVertexBufferArrayData(SCE_CVertexBuffer *vb,
                                                     SCE_CVertexArrayData *data,
                                                     unsigned int n_vertices)
{
    SCE_CVertexBufferData *vbd = NULL;
    if (!(vbd = SCE_CCreateVertexBufferData ()))
        SCEE_LogSrc ();
    else {
        SCE_CSetVertexBufferDataArrayData (vbd, data, n_vertices);
        SCE_CAddVertexBufferData (vb, vbd);
#ifdef SCE_DEBUG
        if (vb->n_vertices != 0 && vb->n_vertices != n_vertices) {
            SCEE_SendMsg ("number of given vertices differs from VB's number");
        }
#endif
        vb->n_vertices = n_vertices;
    }
    return vbd;
}
/**
 * \deprecated
 * \todo remove it
 * \brief Adds a new vertex array data built from the given arguments
 * \param attrib,type,size,p used to construct the vertex array data
 * Deprecated function, better to use SCE_CAddVertexBufferData() and
 * SCE_CSetVertexBufferDataArrayData().
 * \sa SCE_CSetVertexBufferDataArrayData(), SCE_CAddVertexBufferData()
 */
SCE_CVertexBufferData* SCE_CAddVertexBufferNewData (SCE_CVertexBuffer *vb,
                                                    unsigned int attrib,
                                                    SCEenum type, int size,
                                                    unsigned int n_vertices,
                                                    void *p)
{
    SCE_CVertexBufferData *data = NULL;
    SCE_CVertexArrayData array;
    array.attrib = attrib;
    array.type = type;
    array.size = size;
    array.data = p;
    if (!(data = SCE_CAddVertexBufferArrayData (vb, &array, n_vertices)))
        SCEE_LogSrc ();
    return data;
}
/**
 * \brief Removes a vertex buffer data from its buffer
 * \sa SCE_CAddVertexBufferData(), SCE_CClearVertexBufferData()
 */
void SCE_CRemoveVertexBufferData (SCE_CVertexBufferData *data)
{
    if (data->vb) {
        SCE_List_Removel (&data->it);
        data->vb = NULL;
    }
}

static void SCE_CUseVAMode (SCE_CVertexBuffer *vb)
{
    SCE_SListIterator *it = NULL;
    SCE_List_ForEach (it, &vb->data) {
        SCE_CVertexBufferData *data = SCE_List_GetData (it);
        SCE_CUseVertexArray (&data->va);
    }
}
static void SCE_CUseVBOMode (SCE_CVertexBuffer *vb)
{
    SCE_SListIterator *it = NULL;
    glBindBuffer (GL_ARRAY_BUFFER, vb->buf.id);
    SCE_List_ForEach (it, &vb->data) {
        SCE_CVertexBufferData *data = SCE_List_GetData (it);
        SCE_CUseVertexArray (&data->va);
    }
}
static void SCE_CUseVAOMode (SCE_CVertexBuffer *vb)
{
    SCE_SListIterator *it = NULL;
    glBindBuffer (GL_ARRAY_BUFFER, vb->buf.id);
    SCE_List_ForEach (it, &vb->data) {
        SCE_CVertexBufferData *data = SCE_List_GetData (it);
        SCE_CCallVertexArraySequence (&data->va);
    }
}
static void SCE_CUseUnifiedVAOMode (SCE_CVertexBuffer *vb)
{
    /* the first vertex array contains the GL VAO sequence */
    SCE_CVertexBufferData *data = NULL;
    data = SCE_List_GetData (SCE_List_GetFirst (&vb->data));
    SCE_CCallVertexArraySequence (&data->va);
}
/**
 * \brief Builds a vertex buffer
 * \param usage GL usage of the buffer
 * \param mode rendering method to use with the vertex buffer
 * \sa SCE_CSetVertexBufferRenderMode(), SCE_CBufferRenderMode
 */
void SCE_CBuildVertexBuffer (SCE_CVertexBuffer *vb, SCEenum usage,
                             SCE_CBufferRenderMode mode)
{
    SCE_CVertexBufferData *data = NULL;

    vb->build_mode = mode;
    if (mode >= SCE_VBO_RENDER_MODE)
        SCE_CBuildBuffer (&vb->buf, GL_ARRAY_BUFFER, usage);

    SCE_CSetVertexBufferRenderMode (vb, mode);
    if (mode == SCE_VAO_RENDER_MODE) {
        SCE_SListIterator *it = NULL;
        /* create one VAO for each vertex array in the vertex buffer */
        SCE_List_ForEach (it, &vb->data) {
            data = SCE_List_GetData (it);
            SCE_CBeginVertexArraySequence (&data->va);
            SCE_CUseVertexArray (&data->va);
            SCE_CEndVertexArraySequence ();
        }
    } else if (mode == SCE_UNIFIED_VAO_RENDER_MODE) {
        /* use the first vertex array as the VAO container */
        data = SCE_List_GetData (SCE_List_GetFirst (&vb->data));
        SCE_CBeginVertexArraySequence (&data->va);
        SCE_CUseVBOMode (vb);
        SCE_CEndVertexArraySequence ();
    }
}

/**
 * \brief Sets up the given render mode
 * \param mode desired render mode
 *
 * Note that if you wish a VAO mode, it has to be specified to
 * SCE_CBuildVertexBuffer().
 * \sa SCE_CBuildVertexBuffer(), SCE_CBufferRenderMode
 */
void SCE_CSetVertexBufferRenderMode (SCE_CVertexBuffer *vb,
                                     SCE_CBufferRenderMode mode)
{
    SCE_FUseVBFunc fun = NULL;
    SCE_SListIterator *it = NULL;

    switch (mode) {
    case SCE_VA_RENDER_MODE:
        vb->use = SCE_CUseVAMode;
        SCE_List_ForEach (it, &vb->data) {
            SCE_CVertexArrayData *data = NULL;
            SCE_CVertexBufferData *vbd = SCE_List_GetData (it);
            data = SCE_CGetVertexArrayData (&vbd->va);
            data->data = vbd->data.data;
        }
        break;

    case SCE_VBO_RENDER_MODE:
#ifdef SCE_DEBUG
        if (vb->build_mode < SCE_VBO_RENDER_MODE) {
            SCEE_SendMsg ("render mode used to build the vertex buffer doesn't "
                          "allow to switch to VBO render mode");
            break;
        }
#endif
        fun = SCE_CUseVBOMode;
    case SCE_VAO_RENDER_MODE:
        if (!fun) {
#ifdef SCE_DEBUG
            if (vb->build_mode != SCE_VAO_RENDER_MODE) {
                SCEE_SendMsg ("render mode used to build the vertex buffer does"
                              "n't allow to switch to VAO render mode");
                break;
            }
#endif
            fun = SCE_CUseVAOMode;
        }
    case SCE_UNIFIED_VAO_RENDER_MODE:
        if (!fun) {
#ifdef SCE_DEBUG
            if (vb->build_mode != SCE_UNIFIED_VAO_RENDER_MODE) {
                SCEE_SendMsg ("render mode used to build the vertex buffer does"
                              "n't allow to switch to unified VAO render mode");
                break;
            }
#endif
            fun = SCE_CUseUnifiedVAOMode;
        }
        SCE_List_ForEach (it, &vb->data) {
            SCE_CVertexArrayData *data = NULL;
            SCE_CVertexBufferData *vbd = SCE_List_GetData (it);
            data = SCE_CGetVertexArrayData (&vbd->va);
            data->data = SCE_BUFFER_OFFSET (vbd->data.first);
        }
        break;
    default:
#ifdef SCE_DEBUG
        SCEE_SendMsg ("unknow buffer render mode %d", mode);
#endif
    }
    if (fun)
        vb->use = fun;
}

/**
 * \brief Calls SCE_CUpdateBuffer() under the buffer of the given vertex buffer
 * \sa SCE_CUpdateBuffer()
 */
void SCE_CUpdateVertexBuffer (SCE_CVertexBuffer *vb)
{
    SCE_CUpdateBuffer (&vb->buf);
}

/**
 * \brief 
 */
void SCE_CUseVertexBuffer (SCE_CVertexBuffer *vb)
{
    vb->use (vb);
    vb_bound = vb;
}

/**
 * \brief 
 */
void SCE_CRenderVertexBuffer (SCEenum prim)
{
    glDrawArrays (prim, 0, vb_bound->n_vertices);
}


/**
 * \brief Gets the core buffer of an index buffer
 */
SCE_CBuffer* SCE_CGetIndexBufferBuffer (SCE_CIndexBuffer *ib)
{
    return &ib->buf;
}

/**
 * \brief 
 */
void SCE_CSetIndexBufferIndices (SCE_CIndexBuffer *ib, SCEenum type,
                                 unsigned int n_indices, void *indices)
{
    ib->data.size = n_indices * SCE_CSizeof (type);
    ib->data.data = indices;
    ib->ia.type = type;
    /* don't set ib->ia.data, coz it's just an offset */
    ib->n_indices = n_indices;
}

/**
 * \brief 
 */
void SCE_CBuildIndexBuffer (SCE_CIndexBuffer *ib, SCEenum usage)
{
    SCE_CBuildBuffer (&ib->buf, GL_ELEMENT_ARRAY_BUFFER, usage);
}

/**
 * \brief 
 */
void SCE_CUseIndexBuffer (SCE_CIndexBuffer *ib)
{
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ib->buf.id);
    ib_bound = ib;
}

/**
 * \brief 
 */
void SCE_CRenderVertexBufferIndexed (SCEenum prim)
{
    SCE_CRenderIndexed (prim, &ib_bound->ia, ib_bound->n_indices);
}
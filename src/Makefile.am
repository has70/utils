lib_LTLIBRARIES = libsceutils.la

libsceutils_la_CPPFLAGS = -I$(srcdir)/../include
libsceutils_la_CFLAGS   = @PTHREAD_CFLAGS@ \
                          @SCE_DEBUG_CFLAGS@ \
                          @SCE_DEBUG_CFLAGS_EXPORT@
libsceutils_la_LIBADD   = @PTHREAD_LIBS@
libsceutils_la_LDFLAGS  = -version-info @SCE_UTILS_LTVERSION@
libsceutils_la_SOURCES  = SCELine.c \
                          SCEVector.c \
                          SCEMemory.c \
                          SCEArray.c \
                          SCEUtils.c \
                          SCEInert.c \
                          SCEError.c \
                          SCEString.c \
                          SCEResource.c \
                          SCEMatrix.c \
                          SCEListFastForeach.c \
                          SCERectangle.c \
                          SCEPlane.c \
                          SCEMath.c \
                          SCEMedia.c \
                          SCEQuaternion.c \
                          SCETime.c \
                          SCEList.c \
                          SCEType.c \
                          SCEBacktracer.c


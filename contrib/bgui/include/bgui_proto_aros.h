#ifndef BGUI_PROTO_H
#define BGUI_PROTO_H
/*
 * @(#) $Header$
 *
 * $VER: proto/bgui.h 41.10 (20.1.97)
 * bgui.library prototypes. For use with AROS only.
 *
 *
 *
 */

#ifndef AROS_SYSTEM_H
#include <aros/system.h>
#endif

#include <clib/bgui_protos.h>

#if defined(_AMIGA) && defined(__GNUC__)
#include <inline/bgui.h>
#else
#include <defines/bgui.h>
#endif

#endif /* PROTO_BGUI_H */

/*
        Copyright � 1995-2002, The AROS Development Team. All rights reserved.
    $Id$

    Desc:
    Lang: english
*/
#include "rexxsyslib_intern.h"

/*****************************************************************************

    NAME */
#include <clib/rexxsyslib_protos.h>

	AROS_LH3(struct RexxMsg *, CreateRexxMsg,

/*  SYNOPSIS */
	AROS_LHA(struct MsgPort *, port     , A0),
	AROS_LHA(UBYTE          *, extension, A1),
	AROS_LHA(UBYTE          *, host     , D0),

/*  LOCATION */
	struct Library *, RexxSysBase, 24, RexxSys)

/*  FUNCTION

    INPUTS

    RESULT

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS


*****************************************************************************/
{
    AROS_LIBFUNC_INIT
    AROS_LIBBASE_EXT_DECL(struct Library *,RexxSysBase)

    aros_print_not_implemented ("CreateRexxMsg");

    AROS_LIBFUNC_EXIT
} /* CreateRexxMsg */

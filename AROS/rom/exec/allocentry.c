/*
    (C) 1995-96 AROS - The Amiga Replacement OS
    $Id$
    $Log$
    Revision 1.8  1997/01/01 03:46:05  ldp
    Committed Amiga native (support) code

    Changed clib to proto

    Revision 1.7  1996/12/10 13:51:36  aros
    Moved all #include's in the first column so makedepend can see it.

    Revision 1.6  1996/10/24 15:50:43  aros
    Use the official AROS macros over the __AROS versions.

    Revision 1.5  1996/09/13 17:51:22  digulla
    Use IPTR

    Revision 1.4  1996/08/13 13:55:57  digulla
    Replaced AROS_LA by AROS_LHA
    Replaced some AROS_LH*I by AROS_LH*
    Sorted and added includes

    Revision 1.3  1996/08/01 17:41:04  digulla
    Added standard header for all files

    Desc:
    Lang:
*/
#include "exec_intern.h"
#include <aros/libcall.h>
#include <exec/memory.h>
#include <proto/exec.h>

/*****************************************************************************

    NAME */

	AROS_LH1(struct MemList *, AllocEntry,

/*  SYNOPSIS */
	AROS_LHA(struct MemList *, entry, A0),

/*  LOCATION */
	struct ExecBase *, SysBase, 37, Exec)

/*  FUNCTION
	Allocate a number of memory blocks through a MemList structure.

    INPUTS
	entry - The MemList with one MemEntry for each block you want to get

    RESULT
	The allocation was successful if the most significant bit of the
	result is 0. The result then contains a pointer to a copy of
	the MemList structure with the me_Addr fields filled.
	If the most significant bit is set the result contains the type of
	memory that couldn't be allocated.

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO
	FreeEntry()

    INTERNALS

    HISTORY
	18-10-95    created by m. fleischer

******************************************************************************/
{
    AROS_LIBFUNC_INIT

    struct MemList *ret;
    ULONG mlsize,i;

    /* Calculate size of a MemList with ml_NumEntries MemEntries. */
    mlsize=sizeof(struct MemList)-sizeof(struct MemEntry)+
	   sizeof(struct MemEntry)*entry->ml_NumEntries;

    /* Get the MemList structure */
    ret=(struct MemList *)AllocMem(mlsize,MEMF_PUBLIC);

    /* Check nasty case where the returncode is misleading :-( */
    if((IPTR)ret&0x80ul<<(sizeof(APTR)-1)*8)
    {
	FreeMem(ret,mlsize);
	ret=NULL;
    }

    /* The allocation failed? Return "no public memory" */
    if(ret==NULL)
	return (struct MemList *)(MEMF_PUBLIC|0x80ul<<(sizeof(APTR)-1)*8);

    /* Init new struct */
    ret->ml_NumEntries=entry->ml_NumEntries;
    ret->ml_Node.ln_Type=0;
    ret->ml_Node.ln_Pri =0;
    ret->ml_Node.ln_Name=NULL;

    /* Fill all entries */
    for(i=0;i<entry->ml_NumEntries;i++)
    {
	/* Get one */
	ret->ml_ME[i].me_Addr=AllocMem(entry->ml_ME[i].me_Length,
				       entry->ml_ME[i].me_Reqs);
	/* Got it? */
	if(ret->ml_ME[i].me_Addr==NULL)
	{
	    /* No. Set returncode to "none of the 'ml_ME[i].me_Reqs' memory". */
	    entry=(struct MemList *)
		  ((IPTR)entry->ml_ME[i].me_Reqs|0x80ul<<(sizeof(APTR)-1)*8);

	    /* Free everything allocated until now... */
	    for(;i-->0;)
		FreeMem(ret->ml_ME[i].me_Addr,ret->ml_ME[i].me_Length);

	    /* ...including the MemList */
	    FreeMem(ret,mlsize);

	    /* All done */
	    return entry;
	}
	/* Copy the Length field */
	ret->ml_ME[i].me_Length=entry->ml_ME[i].me_Length;
    }
    /* Everything filled. Return OK. */
    return ret;
    AROS_LIBFUNC_EXIT
} /* AllocEntry */


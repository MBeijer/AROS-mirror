/*
    (C) 1997-99 AROS - The Amiga Research OS
    $Id$

    Desc:
    Lang: English
*/
#
#include "datatypes_intern.h"
#include <proto/exec.h>
#include <proto/dos.h>
#include <utility/tagitem.h>
#include <dos/dos.h>
#include <datatypes/datatypesclass.h>
#include <libraries/iffparse.h>

/*****************************************************************************

    NAME */

	AROS_LH3(struct DataType *, ObtainDataTypeA,

/*  SYNOPSIS */
	AROS_LHA(ULONG           , type, D0),
	AROS_LHA(APTR            , handle, A0),
	AROS_LHA(struct TagItem *, attrs, A1),

/*  LOCATION */
	struct Library *, DTBase, 6, DataTypes)

/*  FUNCTION

    Examine the data pointed to by 'handle'.

    INPUTS

    type    --  type of 'handle'
    handle  --  handle to examine (if 'type' is DTST_FILE, 'handle' should be
                a BPTR lock; if it's DTST_CLIPBOARD, 'handle' should be a
		struct IFFHandle *).
    attrs   --  additional attributes (currently none defined).

    RESULT

    A pointer to a DataType or NULL if failure. IoErr() gives more information
    in the latter case:

    ERROR_NO_FREE_STORE     --  Not enough memory available
    ERROR_OBJECT_NOT_FOUND  --  Unable to open the data type object
    ERROR_NOT_IMPLEMENTED   --  Unknown handle type

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    ReleaseDataType()

    INTERNALS

    HISTORY

*****************************************************************************/
{
    AROS_LIBFUNC_INIT

    struct CompoundDatatype *cdt = NULL;
   
    ObtainSemaphoreShared(&(GPB(DTBase)->dtb_DTList->dtl_Lock));
    
    switch(type)
    {
    case DTST_FILE:
	{
	    struct FileInfoBlock *fib;

	    if((fib = AllocDosObject(DOS_FIB, TAG_DONE)) != NULL)
	    {
		cdt = ExamineLock((BPTR)handle, fib, DTBase);
		FreeDosObject(DOS_FIB, fib);
	    }
	    break;
	}
    case DTST_CLIPBOARD:
	{
	    struct ClipboardHandle *cbh;
	    UBYTE                   CheckArray[64];
	    
	    cbh = (struct ClipboardHandle *)((struct IFFHandle *)handle)->iff_Stream;
	    
	    cbh->cbh_Req.io_ClipID = 0;
	    cbh->cbh_Req.io_Error = 0;
	    cbh->cbh_Req.io_Offset = 0;
	    cbh->cbh_Req.io_Command = CMD_READ;
	    cbh->cbh_Req.io_Data = CheckArray;
	    cbh->cbh_Req.io_Length = sizeof(CheckArray);
	    
	    if(DoIO((struct IORequest*)&cbh->cbh_Req))
		SetIoErr(ERROR_OBJECT_NOT_FOUND);
	    else
	    {
		cbh->cbh_Req.io_Error = 0;
		cbh->cbh_Req.io_Offset = 0;
		
		if(cbh->cbh_Req.io_Actual < 12)
		    SetIoErr(ERROR_OBJECT_NOT_FOUND);
		else
		{
		    struct DTHookContext dthc;
		    
		    dthc.dthc_SysBase = (struct Library *)SysBase;
		    dthc.dthc_DOSBase = DOSBase;
		    dthc.dthc_IFFParseBase = IFFParseBase;
		    dthc.dthc_UtilityBase = UtilityBase;
		    dthc.dthc_Lock = NULL;
		    dthc.dthc_FIB = NULL;
		    dthc.dthc_FileHandle = NULL;
		    dthc.dthc_IFF = (struct IFFHandle *)handle;
		    dthc.dthc_Buffer = CheckArray;
		    dthc.dthc_BufferLength = cbh->cbh_Req.io_Actual;
		    
		    cdt = ExamineData(DTBase,
				      &dthc,
				      CheckArray,
				      (UWORD)cbh->cbh_Req.io_Actual,
				      "",
				      NULL);
		}
	    }
	}
	break;
	
    default:
	SetIoErr(ERROR_NOT_IMPLEMENTED);
	break;
    }
    
    if(cdt)
	cdt->OpenCount++;
    
    ReleaseSemaphore(&(GPB(DTBase)->dtb_DTList->dtl_Lock));
    
    if(IoErr() == ERROR_OBJECT_NOT_FOUND)
	SetIoErr(DTERROR_COULDNT_OPEN);
    
    return (struct DataType *)cdt;
    
    AROS_LIBFUNC_EXIT
} /* ObtainDataTypeA */

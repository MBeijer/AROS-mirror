/*
    (C) 1995-96 AROS - The Amiga Research OS
    $Id$

    Desc: Graphics function XorRectRegion()
    Lang: english
*/
#include "graphics_intern.h"
#include <graphics/regions.h>
#include "intregions.h"

/*****************************************************************************

    NAME */
#include <proto/graphics.h>

	AROS_LH2(BOOL, XorRectRegion,

/*  SYNOPSIS */
	AROS_LHA(struct Region    *, region,    A0),
	AROS_LHA(struct Rectangle *, rectangle, A1),

/*  LOCATION */
	struct GfxBase *, GfxBase, 93, Graphics)

/*  FUNCTION
	Exclusive-OR the given rectangle to the given
	region

    INPUTS
	region - pointer to a region structure
	rectangle - pointer to a rectangle structure

    RESULT
	TRUE if the operation was succesful, else FALSE
	(out of memory)

    NOTES
	All relevant data is copied, you may throw away the
	given rectangle after calling this function

    EXAMPLE

    BUGS

    SEE ALSO
	AndRectRegion(), OrRectRegion(), ClearRectRegion()

    INTERNALS

    HISTORY
	27-11-96    digulla automatically created from
			    graphics_lib.fd and clib/graphics_protos.h
	19-01-97    mreckt  intital version

*****************************************************************************/
{
    AROS_LIBFUNC_INIT
#if USE_BANDED_FUNCTIONS

    return _XorRectRegion(region, rectangle, GfxBase);

#else

    struct Region* intersection, *copy2;

    if ((intersection = CopyRegion(region)))
    {
        if ((copy2 = CopyRegion(region)))
	{
	    AndRectRegion(intersection, rectangle);

	    if (OrRectRegion(region, rectangle))
	    {
		if (intersection->RegionRectangle)
		{
		    BOOL result;

		    if (!(result = ClearRegionRegion(intersection, region)))
		    {
		        /* reinstall old RegionRectangles and bounds*/
			struct Region tmp;
			tmp     = *region;
			*region = *copy2;
			*copy2  = tmp;
		    }
		    DisposeRegion(intersection);
		    DisposeRegion(copy2);
		    return result;
		}

		DisposeRegion(intersection);
		DisposeRegion(copy2);
		return TRUE;
	    }
	    DisposeRegion(copy2);
	}
	DisposeRegion(intersection);
    }
    return FALSE;
#endif
    AROS_LIBFUNC_EXIT

} /* XorRectRegion */

#include <aros/kernel.h>
#include <aros/libcall.h>

#include <kernel_base.h>

/*****************************************************************************

    NAME */
#include <proto/kernel.h>

AROS_LH0I(void, KrnCli,

/*  SYNOPSIS */

/*  LOCATION */
	struct KernelBase *, KernelBase, 9, Kernel)

/*  FUNCTION
	Instantly disable interrupts.

    INPUTS
	None

    RESULT
	None

    NOTES
	This is low level function, it does not have nesting count
	and state tracking mechanism. It operates directly on the CPU.
	Normal applications should consider using exec.library/Disable().

    EXAMPLE

    BUGS

    SEE ALSO
	KrnSti()

    INTERNALS

******************************************************************************/
{
    AROS_LIBFUNC_INIT

    asm volatile ("move.w #0x4000,0xdff09a\n");

    AROS_LIBFUNC_EXIT
}

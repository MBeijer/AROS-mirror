/*
    (C) 1995-96 AROS - The Amiga Replacement OS
    $Id$
    $Log$
    Revision 1.4  1996/08/16 14:04:08  digulla
    Fixed bug in docs. Bugfix in code is still pending.

    Revision 1.3  1996/08/13 13:52:50  digulla
    Replaced <dos/dosextens.h> by "dos_intern.h" or added "dos_intern.h"
    Replaced __AROS_LA by __AROS_LHA

    Revision 1.2  1996/08/01 17:40:56  digulla
    Added standard header for all files

    Desc:
    Lang: english
*/
#include <exec/memory.h>
#include <clib/exec_protos.h>
#include <dos/rdargs.h>
#include <dos/dosextens.h>
#include "dos_intern.h"

/*****************************************************************************

    NAME */
	#include <clib/dos_protos.h>

	__AROS_LH3(struct RDArgs *, ReadArgs,

/*  SYNOPSIS */
	__AROS_LHA(STRPTR,          template, D1),
	__AROS_LHA(LONG *,          array,    D2),
	__AROS_LHA(struct RDArgs *, rdargs,   D3),

/*  LOCATION */
	struct DosLibrary *, DOSBase, 133, Dos)

/*  FUNCTION
	Parses the commandline, a given string or Input() and fills
	an argument array according to the options template given.
	The array must be initialized to the wanted defaults before
	each call to ReadArgs(). If the rdargs argument is NULL
	ReadArgs() tries to parse the commandline and continues
	on the input channel if it just consists of a single '?',
	prompting the user for input.

    INPUTS
	template - Template string. The template string is given as
		   a number of options separated by ',' and modified
		   by '/' modifiers, e.g. 'NAME,WIDTH/N,HEIGHT/N'
		   means get a name string and two numbers (width and
		   height). The possible modifiers are:
		   /S Option is a switch. It may be either set or
		      left out.
		   /T Option is a boolean value. Requires an argument
		      which may be "ON", "YES" (setting the respective
		      argument to 1), "OFF" or "NO" (setting the
		      respective argument to 0).
		   /N Option is a number. Strings are not allowed.
		      If the option is optional, a pointer to the
		      actual number is returned. This is how you know
		      if it was really given.
		   /A Argument is required. If it is left out ReadArgs()
		      fails.
		   /K The keyword must be given when filling the option.
		      Normally it's skipped.
		   /M Multiple strings. The result is returned as a string
		      pointer array terminated with NULL. /M eats all strings
		      that don't fit into any other option. If there are
		      unfilled /A arguments after parsing they steal strings
		      from /M. This makes it possible to e.g. write a COPY
		      template like 'FROM/A/M,TO/A'. There may be only one
		      /M option in a template.
		   /F Eats the rest of the line even if there are option
		      keywords in it.
	array	 - Array to be filled with the result values. The array must
		   be intialized to the default values before calling
		   ReadArgs().
	rdargs	 - An optional RDArgs structure determinating the type of
		   input to process.

    RESULT
	A handle for the memory allocated by ReadArgs(). Must be freed
	with FreeArgs() later.

    NOTES

    EXAMPLE

    BUGS
	The rdargs argument is currently ignored.

    SEE ALSO
	FreeArgs(), Input()

    INTERNALS

    HISTORY
	29-10-95    digulla automatically created from
			    dos_lib.fd and clib/dos_protos.h

*****************************************************************************/
{
    __AROS_FUNC_INIT
    __AROS_BASE_EXT_DECL(struct DosLibrary *,DOSBase)

    /* Allocated resources */
    struct RDArgs *rda=NULL;
    struct DAList *dalist=NULL;
    UBYTE *flags=NULL;
    STRPTR strbuf=NULL, iline=NULL;
    STRPTR *multvec=NULL, *argbuf=NULL;
    ULONG multnum=0, multmax=0;

    /* Some variables */
    STRPTR s1, s2, *newmult;
    ULONG arg, numargs, nextarg;
    LONG it, item, chars, value;
    struct CSource cs;

    /* Get pointer to process structure. */
    struct Process *me=(struct Process *)FindTask(NULL);

    /* Error recovery. C has no exceptions. This is a simple replacement. */
    LONG error;
#define ERROR(a) { error=a; goto end; }

/* Template options */
#define REQUIRED 0x80 /* /A */
#define KEYWORD  0x40 /* /K */
#define TYPEMASK 0x07
#define NORMAL	 0x00 /* No option */
#define SWITCH	 0x01 /* /S, implies /K */
#define TOGGLE	 0x02 /* /T, implies /K */
#define NUMERIC  0x03 /* /N */
#define MULTIPLE 0x04 /* /M */
#define REST	 0x05 /* /F */

    /* Flags for each possible character. */
    static const UBYTE argflags[]=
    { REQUIRED, 0, 0, 0, 0, REST, 0, 0, 0, 0, KEYWORD, 0, MULTIPLE,
      NUMERIC, 0, 0, 0, 0, SWITCH|KEYWORD, TOGGLE|KEYWORD, 0, 0, 0, 0, 0, 0 };

    /* Allocate readargs structure (and private internal one) */
    rda=(struct RDArgs *)AllocVec(sizeof(struct RDArgs),MEMF_ANY);
    dalist=(struct DAList *)AllocVec(sizeof(struct DAList),MEMF_ANY);
    if(rda==NULL||dalist==NULL)
	ERROR(ERROR_NO_FREE_STORE);

    /* Init character source. */
    cs.CS_Buffer=me->pr_Arguments;
    s1=cs.CS_Buffer;
    while(*s1++)
	;
    cs.CS_Length=s1-cs.CS_Buffer-1;
    cs.CS_CurChr=0;

    /* Check commandline for a single '?' */
    s1=cs.CS_Buffer;
    /* Skip leading whitespace */
    while(*s1==' '||*s1=='\t')
	s1++;
    /* Check for '?' */
    if(*s1++=='?')
    {
	/* Skip whitespace */
	while(*s1==' '||*s1=='\t')
	    s1++;
	/* Check for EOL */
	if(*s1=='\n'||!*s1)
	{
	    /* Only a single '?' on the commandline. */
	    BPTR input=me->pr_CIS, output=me->pr_COS;
	    ULONG isize=0, ibuf=0;
	    LONG c;
	    /* Prompt for more input */
	    if(FPuts(output,template)||FPuts(output,": ")||!Flush(output))
	       ERROR(me->pr_Result2);
	    /* Read a line in. */
	    for(;;)
	    {
		if(isize>=ibuf)
		{
		    /* Buffer too small. Get a new one. */
		    STRPTR newiline;
		    ibuf+=256;
		    newiline=(STRPTR)AllocVec(ibuf,MEMF_ANY);
		    if(newiline==NULL)
			ERROR(ERROR_NO_FREE_STORE);
		    CopyMemQuick((ULONG *)iline,(ULONG *)newiline,isize);
		    FreeVec(iline);
		    iline=newiline;
		}
		/* Read character */
		c=FGetC(input);
		/* Check and write it. */
		if(c==EOF&&me->pr_Result2)
		    ERROR(me->pr_Result2);
		if(c==EOF||c=='\n'||!c)
		    break;
		iline[isize++]=c;
	    }
	    /* Prepare input source for new line. */
	    cs.CS_Buffer=iline;
	    cs.CS_Length=isize;
	}
    }

    /*
	Get enough space for string buffer.
	It's always smaller than the size of the input line+1.
    */
    strbuf=(STRPTR)AllocVec(cs.CS_Length+1,MEMF_ANY);
    if(strbuf==NULL)
	ERROR(ERROR_NO_FREE_STORE);

    /* TODO: rdargs!=NULL */

    /* Count the number of items in the template (number of ','+1). */
    numargs=1;
    s1=template;
    while(*s1)
	if(*s1++==',')
	    numargs++;

    /* Use this count to get space for temporary flag array and result buffer. */
    flags=(UBYTE *)AllocVec(numargs+1,MEMF_CLEAR);
    argbuf=(STRPTR *)AllocVec((numargs+1)*sizeof(STRPTR),MEMF_CLEAR);
    if(flags==NULL||argbuf==NULL)
	ERROR(ERROR_NO_FREE_STORE);

    /* Fill the flag array. */
    s1=template;
    s2=flags;
    while(*s1)
    {
	/* A ',' means: goto next item. */
	if(*s1==',')
	    s2++;
	/* In case of a '/' use the next character as option. */
	if(*s1++=='/')
	    *s2|=argflags[*s1-'A'];
    }
    /* Add a dummy so that the whole line is processed. */
    *++s2=MULTIPLE;

    /*
	Now process commandline for the first time:
	* Go from left to right and fill all items that need filling.
	* If an item is given as 'OPTION=VALUE' or 'OPTION VALUE' fill
	  it out of turn.
    */
    s1=strbuf;
    for(arg=0;arg<=numargs;arg=nextarg)
    {
	nextarg=arg+1;

	/* Skip /K options and options that are already done. */
	if(flags[arg]&KEYWORD||argbuf[arg]!=NULL)
	    continue;

	/* If the current option is of type /F do not look for keywords */
	if((flags[arg]&TYPEMASK)!=REST)
	{
	    /* Get item. Quoted items are no keywords. */
	    it=ReadItem(s1,~0ul/2,&cs);
	    if(it==ITEM_UNQUOTED)
	    {
		/* Not quoted. Check if it's a keyword. */
		item=FindArg(template,s1);
		if(item>=0&&argbuf[item]==NULL)
		{
		    /*
			It's a keyword. Fill it and retry the current option
			at the next turn
		    */
		    nextarg=arg;
		    arg=item;

		    /* /S /T and /F may not be given as 'OPTION=VALUE'. */
		    if((flags[item]&TYPEMASK)!=SWITCH&&
		       (flags[item]&TYPEMASK)!=TOGGLE&&
		       (flags[item]&TYPEMASK)!=REST)
		    {
			/* Get value. */
			it=ReadItem(s1,~0ul/2,&cs);
			if(it==ITEM_EQUAL)
			    it=ReadItem(s1,~0ul/2,&cs);
		    }
		}
	    }
	    /* Check returncode of ReadItem(). */
	    if(it==ITEM_EQUAL)
		ERROR(ERROR_BAD_TEMPLATE);
	    if(it==ITEM_ERROR)
		ERROR(me->pr_Result2);
	    if(it==ITEM_NOTHING)
		break;
	}
	/* /F takes all the rest */
	if((flags[arg]&TYPEMASK)==REST)
	{
	    /* Skip leading whitespace */
	    while(cs.CS_CurChr<cs.CS_Length&&
		  (cs.CS_Buffer[cs.CS_CurChr]==' '||
		   cs.CS_Buffer[cs.CS_CurChr]=='\t'))
		cs.CS_CurChr++;

	    /* Find the last non-whitespace character */
	    s2=s1-1;
	    argbuf[arg]=s1;
	    while(cs.CS_CurChr<cs.CS_Length&&
		  cs.CS_Buffer[cs.CS_CurChr]&&
		  cs.CS_Buffer[cs.CS_CurChr]!='\n')
	    {
		if(cs.CS_Buffer[cs.CS_CurChr]!=' '&&
		   cs.CS_Buffer[cs.CS_CurChr]!='\t')
		    s2=s1;
		/* Copy string by the way. */
		*s1++=cs.CS_Buffer[cs.CS_CurChr++];
	    }
	    /* Add terminator (1 after the character found). */
	    s2[1]=0;
	    it=ITEM_NOTHING;
	    break;
	}
	/* /S or /T just set a flag */
	if((flags[arg]&TYPEMASK)==SWITCH||(flags[arg]&TYPEMASK)==TOGGLE)
	    argbuf[arg]=(char *)1;
	else if((flags[arg]&TYPEMASK)==MULTIPLE)
	{
	    /* All /M arguments are stored in a buffer. */
	    if(multnum>=multmax)
	    {
		/* Buffer too small. Get a new one. */
		multmax+=16;
		newmult=(STRPTR *)AllocVec(multmax*sizeof(char *),MEMF_ANY);
		if(newmult==NULL)
		    ERROR(ERROR_NO_FREE_STORE);
		CopyMemQuick((ULONG *)multvec,(ULONG *)newmult,multnum*sizeof(char *));
		FreeVec(multvec);
		multvec=newmult;
	    }
	    /* Put string into the buffer. */
	    multvec[multnum++]=s1;
	    while(*s1++)
		;
	    /* /M takes more than one argument, so retry. */
	    nextarg=arg;
	}else /* NORMAL || NUMERIC */
	{
	    /* Put argument into argument buffer. */
	    argbuf[arg]=s1;
	    while(*s1++)
		;
	}
    }

    /* Unfilled /A options steal Arguments from /M */
    for(arg=numargs;arg-->0;)
	if(flags[arg]&REQUIRED&&argbuf[arg]==NULL&&
	   (flags[arg]&TYPEMASK)!=MULTIPLE)
	{
	    if(!multnum)
		/* No arguments left? Oh dear! */
		ERROR(ERROR_REQUIRED_ARG_MISSING);
	    argbuf[arg]=multvec[--multnum];
	}

    /* Put the rest of /M where it belongs */
    for(arg=0;arg<numargs;arg++)
	if((flags[arg]&TYPEMASK)==MULTIPLE)
	{
	    if(flags[arg]&REQUIRED&&!multnum)
		ERROR(ERROR_REQUIRED_ARG_MISSING);

	    /* NULL terminate it. */
	    if(multnum>=multmax)
	    {
		multmax+=16;
		newmult=(STRPTR *)AllocVec(multmax*sizeof(STRPTR),MEMF_ANY);
		if(newmult==NULL)
		    ERROR(ERROR_NO_FREE_STORE);
		CopyMemQuick((ULONG *)multvec,(ULONG *)newmult,multnum*sizeof(char *));
		FreeVec(multvec);
		multvec=newmult;
	    }
	    multvec[multnum++]=NULL;
	    argbuf[arg]=(STRPTR)multvec;
	    break;
	}

    /* There are some arguments left? Return error. */
    if(multnum&&arg==numargs)
	ERROR(ERROR_TOO_MANY_ARGS);

    /*
	The commandline is processed now. Put the results in the result array.
	Convert /N arguments by the way.
    */
    for(arg=0;arg<numargs;arg++)
    {
	/* Just for the arguments given. */
	if(argbuf[arg]!=NULL)
	{
	    switch(flags[arg]&TYPEMASK)
	    {
		case NORMAL:
		case MULTIPLE:
		case REST:
		case SWITCH:
		    /* Simple arguments are just copied. */
		    array[arg]=(LONG)argbuf[arg];
		    break;
		case TOGGLE:
		    /* /T logically inverts the argument. */
		    array[arg]=!array[arg];
		    break;
		case NUMERIC:
		    /* Convert /N argument. */
		    chars=StrToLong(argbuf[arg],&value);
		    if(chars<=0||argbuf[arg][chars])
			/* Conversion failed. */
			ERROR(ERROR_BAD_NUMBER);
		    /* Put the result where it belongs. */
		    if(flags[arg]&REQUIRED)
			/* Required argument. Return number. */
			array[arg]=value;
		    else
		    {
			/* Abuse the argbuf buffer. It's not needed anymore. */
			argbuf[arg]=(STRPTR)value;
			array[arg]=(LONG)&argbuf[arg];
		    }
		    break;
	    }
	}
    }

    /* All OK. */
    error=0;
end:
    /* Cleanup and return. */
    FreeVec(iline);
    FreeVec(flags);
    if(error)
    {
	/* ReadArgs() failed. Clean everything up. */
	FreeVec(rda);
	FreeVec(dalist);
	FreeVec(argbuf);
	FreeVec(strbuf);
	FreeVec(multvec);
	me->pr_Result2=error;
	return NULL;
    }else
    {
	/* All went well. Prepare result and return. */
	rda->RDA_DAList=(LONG)dalist;
	dalist->ArgBuf=argbuf;
	dalist->StrBuf=strbuf;
	dalist->MultVec=multvec;
	return rda;
    }
    __AROS_FUNC_EXIT
} /* ReadArgs */

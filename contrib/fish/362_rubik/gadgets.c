/*	gadgets for rubik   MJR 1st Feb '90 (ain't touched this for a month! */

#include "header.c"

struct TextAttr ta = 
{
"topaz.font",
8,
0,
FPF_ROMFONT
};

unsigned char rollrightdata[] =
{
0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x03,0xC0,
0x00,0x00,0x03,0xC0,0xFF,0x00,0x07,0xC0,0xFE,0x00,0x07,0x80,
0xFC,0x00,0x0F,0x80,0xFE,0x00,0x3F,0x00,0xFF,0x80,0xFE,0x00,0xFF,0xFF,0xFC,0x00,
0xCF,0xFF,0xF8,0x00,0x83,0xFF,0xE0,0x00,0x00,0x7F,0x00,0x00,
0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x03,0xC0,
0x00,0x00,0x03,0xC0,0xFF,0x00,0x07,0xC0,0xFE,0x00,0x07,0x80,
0xFC,0x00,0x0F,0x80,0xFE,0x00,0x3F,0x00,0xFF,0x80,0xFE,0x00,0xFF,0xFF,0xFC,0x00,
0xCF,0xFF,0xF8,0x00,0x83,0xFF,0xE0,0x00,0x00,0x7F,0x00,0x00,
0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x03,0xC0,
0x00,0x00,0x03,0xC0,0xFF,0x00,0x07,0xC0,0xFE,0x00,0x07,0x80,
0xFC,0x00,0x0F,0x80,0xFE,0x00,0x3F,0x00,0xFF,0x80,0xFE,0x00,0xFF,0xFF,0xFC,0x00,
0xCF,0xFF,0xF8,0x00,0x83,0xFF,0xE0,0x00,0x00,0x7F,0x00,0x00
};

unsigned char rollleftdata[] =
{
0x00,0x7F,0x00,0x00,0x83,0xFF,0xE0,0x00,0xCF,0xFF,0xF8,0x00,0xFF,0xFF,0xFC,0x00,
0xFF,0x80,0xFE,0x00,0xFE,0x00,0x3F,0x00,0xFC,0x00,0x0F,0x80,
0xFE,0x00,0x07,0x80,0xFF,0x00,0x07,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,
0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,
0x00,0x7F,0x00,0x00,0x83,0xFF,0xE0,0x00,0xCF,0xFF,0xF8,0x00,0xFF,0xFF,0xFC,0x00,
0xFF,0x80,0xFE,0x00,0xFE,0x00,0x3F,0x00,0xFC,0x00,0x0F,0x80,
0xFE,0x00,0x07,0x80,0xFF,0x00,0x07,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,
0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,
0x00,0x7F,0x00,0x00,0x83,0xFF,0xE0,0x00,0xCF,0xFF,0xF8,0x00,0xFF,0xFF,0xFC,0x00,
0xFF,0x80,0xFE,0x00,0xFE,0x00,0x3F,0x00,0xFC,0x00,0x0F,0x80,
0xFE,0x00,0x07,0x80,0xFF,0x00,0x07,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x03,0xC0,
0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xE0
};

unsigned char yawleftdata[] =
{
0x00,0x1E,0x03,0xE0,0x7E,0x00,0xC0,0x00,0xE0,0x00,0xFF,0xC0,0xFF,0xE0,
0xFF,0xF0,0xFF,0xFA,0xFF,0xFC,0xFF,0xF8,0xFF,0xF0,0x7F,0xE0,0x1F,0xC0,
0x00,0x1E,0x03,0xE0,0x7E,0x00,0xC0,0x00,0xE0,0x00,0xFF,0xC0,0xFF,0xE0,
0xFF,0xF0,0xFF,0xFA,0xFF,0xFC,0xFF,0xF8,0xFF,0xF0,0x7F,0xE0,0x1F,0xC0,
0x00,0x1E,0x03,0xE0,0x7E,0x00,0xC0,0x00,0xE0,0x00,0xFF,0xC0,0xFF,0xE0,
0xFF,0xF0,0xFF,0xFA,0xFF,0xFC,0xFF,0xF8,0xFF,0xF0,0x7F,0xE0,0x1F,0xC0
};

unsigned char yawrightdata[] =
{
0xF0,0x00,0x0F,0x80,0x00,0xFC,0x00,0x06,0x00,0x0E,0x07,0xFE,0x0F,0xFE,
0x1F,0xFE,0xBF,0xFE,0x7F,0xFE,0x3F,0xFE,0x1F,0xFE,0x0F,0xFC,0x07,0xF0,
0xF0,0x00,0x0F,0x80,0x00,0xFC,0x00,0x06,0x00,0x0E,0x07,0xFE,0x0F,0xFE,
0x1F,0xFE,0xBF,0xFE,0x7F,0xFE,0x3F,0xFE,0x1F,0xFE,0x0F,0xFC,0x07,0xF0,
0xF0,0x00,0x0F,0x80,0x00,0xFC,0x00,0x06,0x00,0x0E,0x07,0xFE,0x0F,0xFE,
0x1F,0xFE,0xBF,0xFE,0x7F,0xFE,0x3F,0xFE,0x1F,0xFE,0x0F,0xFC,0x07,0xF0
};

unsigned char climbdata[] =
{
0x1F,0xF0,0x3F,0xF8,0x2F,0xF8,0x27,0xFC,0x27,0xFC,
0x27,0xFC,0x67,0xFC,0x47,0xFC,0x47,0xFC,0x47,0xFC,
0x43,0xF8,0x81,0xF0,0x80,0xE0,0x80,0x40,0x80,0x80,
0x1F,0xF0,0x3F,0xF8,0x2F,0xF8,0x27,0xFC,0x27,0xFC,
0x27,0xFC,0x67,0xFC,0x47,0xFC,0x47,0xFC,0x47,0xFC,
0x43,0xF8,0x81,0xF0,0x80,0xE0,0x80,0x40,0x80,0x80,
0x1F,0xF0,0x3F,0xF8,0x2F,0xF8,0x27,0xFC,0x27,0xFC,
0x27,0xFC,0x67,0xFC,0x47,0xFC,0x47,0xFC,0x47,0xFC,
0x43,0xF8,0x81,0xF0,0x80,0xE0,0x80,0x40,0x80,0x80
};

unsigned char divedata[] =
{
0x80,0x80,0x80,0x40,0x80,0xE0,0x81,0xF0,0x43,0xF8,
0x47,0xFC,0x47,0xFC,0x47,0xFC,0x67,0xFC,0x27,0xFC,
0x27,0xFC,0x27,0xFC,0x2F,0xF8,0x3F,0xF8,0x1F,0xF0,
0x80,0x80,0x80,0x40,0x80,0xE0,0x81,0xF0,0x43,0xF8,
0x47,0xFC,0x47,0xFC,0x47,0xFC,0x67,0xFC,0x27,0xFC,
0x27,0xFC,0x27,0xFC,0x2F,0xF8,0x3F,0xF8,0x1F,0xF0,
0x80,0x80,0x80,0x40,0x80,0xE0,0x81,0xF0,0x43,0xF8,
0x47,0xFC,0x47,0xFC,0x47,0xFC,0x67,0xFC,0x27,0xFC,
0x27,0xFC,0x27,0xFC,0x2F,0xF8,0x3F,0xF8,0x1F,0xF0
};

struct Image col6i =
{
0,0,
7,7,3,
NULL,
0,6,
NULL
};

struct Image col5i =
{
0,0,
7,7,3,
NULL,
0,5,
NULL
};

struct Image col4i =
{
0,0,
7,7,3,
NULL,
0,4,
NULL
};

struct Image col3i =
{
0,0,
7,7,3,
NULL,
0,3,
NULL
};

struct Image col2i =
{
0,0,
7,7,3,
NULL,
0,2,
NULL
};

struct Image col1i =
{
0,0,
7,7,3,
NULL,
0,1,
NULL
};

struct Image rollright =
{
0,0,				/*	LeftEdge, TopEdge		*/
27,14,3,			/*	Width, Height, Depth	*/
&rollrightdata[0],
7,0,				/*	PlanePick, PlaneOnOff	*/
NULL				/*	Pointer to next Image	*/
};

struct Image rollleft =
{
0,0,				/*	LeftEdge, TopEdge		*/
27,14,3,			/*	Width, Height, Depth	*/
&rollleftdata[0],
7,0,				/*	PlanePick, PlaneOnOff	*/
NULL				/*	Pointer to next Image	*/
};

struct Image yawleft =
{
0,0,				/*	LeftEdge, TopEdge		*/
15,14,3,			/*	Width, Height, Depth	*/
&yawleftdata[0],
7,0,				/*	PlanePick, PlaneOnOff	*/
NULL				/*	Pointer to next Image	*/
};

struct Image yawright =
{
0,0,				/*	LeftEdge, TopEdge		*/
15,14,3,			/*	Width, Height, Depth	*/
&yawrightdata[0],
7,0,				/*	PlanePick, PlaneOnOff	*/
NULL				/*	Pointer to next Image	*/
};

struct Image climb =
{
0,0,				/*	LeftEdge, TopEdge		*/
14,15,3,			/*	Width, Height, Depth	*/
&climbdata[0],
7,0,				/*	PlanePick, PlaneOnOff	*/
NULL				/*	Pointer to next Image	*/
};

struct Image dive =
{
0,0,				/*	LeftEdge, TopEdge		*/
14,15,3,			/*	Width, Height, Depth	*/
&divedata[0],
7,0,				/*	PlanePick, PlaneOnOff	*/
NULL				/*	Pointer to next Image	*/
};

struct IntuiText minustext = {0,7,JAM2,0,1,&ta,(UBYTE *)"-",NULL};

struct IntuiText plustext = {0,7,JAM2,0,1,&ta,(UBYTE *)"+",NULL};

struct IntuiText abouttext = {0,7,JAM2,1,1,&ta,(UBYTE *)"ABOUT",NULL};

struct IntuiText helptext = {0,7,JAM2,0,1,&ta,(UBYTE *)"HELP",NULL};

struct IntuiText slowertext = {0,7,JAM2,0,0,&ta,(UBYTE *)"SLOWER",NULL};

struct IntuiText fastertext = {0,7,JAM2,0,0,&ta,(UBYTE *)"FASTER",NULL};

struct IntuiText backtext = {0,7,JAM2,1,1,&ta,(UBYTE *)"BACK",NULL};

struct IntuiText fronttext = {0,7,JAM2,1,1,&ta,(UBYTE *)"FRONT",NULL};

struct Gadget colour6 =
{
NULL,
224,177,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col6i,
NULL,
NULL,
0,
NULL,
27,
NULL
};

struct Gadget colour5 =
{
NULL,
214,177,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col5i,
NULL,
NULL,
0,
NULL,
26,
NULL
};

struct Gadget colour4 =
{
NULL,
204,177,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col4i,
NULL,
NULL,
0,
NULL,
25,
NULL
};

struct Gadget colour3 =
{
NULL,
224,167,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col3i,
NULL,
NULL,
0,
NULL,
24,
NULL
};

struct Gadget colour2 =
{
NULL,
214,167,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col2i,
NULL,
NULL,
0,
NULL,
23,
NULL
};

struct Gadget colour1 =
{
NULL,
204,167,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col1i,
NULL,
NULL,
0,
NULL,
22,
NULL
};

struct Gadget blueminus = 
{
NULL,
301,186,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&minustext,
0,
NULL,
21,
NULL
};

struct Gadget greenminus = 
{
NULL,
277,186,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&minustext,
0,
NULL,
20,
NULL
};

struct Gadget redminus = 
{
NULL,
253,186,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&minustext,
0,
NULL,
19,
NULL
};

struct Gadget blueplus = 
{
NULL,
301,168,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&plustext,
0,
NULL,
18,
NULL
};

struct Gadget greenplus = 
{
NULL,
277,168,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&plustext,
0,
NULL,
17,
NULL
};

struct Gadget redplus = 
{
NULL,
253,168,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&plustext,
0,
NULL,
16,
NULL
};

/*	need this lot twice for AddGadget to work! (sigh!)	*/

struct Gadget colour6a =
{
NULL,
224,177,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col6i,
NULL,
NULL,
0,
NULL,
27,
NULL
};

struct Gadget colour5a =
{
NULL,
214,177,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col5i,
NULL,
NULL,
0,
NULL,
26,
NULL
};

struct Gadget colour4a =
{
NULL,
204,177,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col4i,
NULL,
NULL,
0,
NULL,
25,
NULL
};

struct Gadget colour3a =
{
NULL,
224,167,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col3i,
NULL,
NULL,
0,
NULL,
24,
NULL
};

struct Gadget colour2a =
{
NULL,
214,167,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col2i,
NULL,
NULL,
0,
NULL,
23,
NULL
};

struct Gadget colour1a =
{
NULL,
204,167,7,7,
GADGHCOMP | GADGIMAGE,
RELVERIFY,
BOOLGADGET,
(APTR)&col1i,
NULL,
NULL,
0,
NULL,
22,
NULL
};

struct Gadget blueminusa = 
{
NULL,
301,186,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&minustext,
0,
NULL,
21,
NULL
};

struct Gadget greenminusa = 
{
NULL,
277,186,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&minustext,
0,
NULL,
20,
NULL
};

struct Gadget redminusa = 
{
NULL,
253,186,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&minustext,
0,
NULL,
19,
NULL
};

struct Gadget blueplusa = 
{
NULL,
301,168,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&plustext,
0,
NULL,
18,
NULL
};

struct Gadget greenplusa = 
{
NULL,
277,168,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&plustext,
0,
NULL,
17,
NULL
};

struct Gadget redplusa = 
{
NULL,
253,168,8,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&plustext,
0,
NULL,
16,
NULL
};

struct Gadget setupgadget = 
{
NULL,
199,139,53,9,
GADGHBOX,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
NULL,
0,
NULL,
15,
NULL
};

struct Gadget solvegadget = 
{
&setupgadget,
199,127,53,9,
GADGHBOX,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
NULL,
0,
NULL,
14,
NULL
};

struct Gadget normalgadget = 
{
&solvegadget,
199,115,53,9,
GADGHBOX,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
NULL,
0,
NULL,
13,
NULL
};

struct Gadget aboutgadget = 
{
&normalgadget,
265,139,41,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&abouttext,
0,
NULL,
12,
NULL
};

struct Gadget helpgadget = 
{
&aboutgadget,
270,115,32,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&helptext,
0,
NULL,
11,
NULL
};

struct Gadget slowergadget = 
{
&helpgadget,
261,83,48,7,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&slowertext,
0,
NULL,
10,
NULL
};

struct Gadget fastergadget = 
{
&slowergadget,
200,83,48,7,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&fastertext,
0,
NULL,
9,
NULL
};

struct Gadget backgadget = 
{
&fastergadget,
276,23,33,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&backtext,
0,
NULL,
8,
NULL
};

struct Gadget frontgadget = 
{
&backgadget,
197,23,41,9,
GADGHCOMP,
RELVERIFY,
BOOLGADGET,
NULL,
NULL,
&fronttext,
0,
NULL,
7,
NULL
};

struct Gadget rollrightgadget =
{
&frontgadget,
244,56,27,14,		/*	posn. and size	*/
GADGHCOMP |
GADGIMAGE,			/*	flags			*/
RELVERIFY,			/*	activation		*/
BOOLGADGET,			/*	gadget type		*/
(APTR)&rollright,	/*	image pointer	*/
NULL,				/*	alternate image	*/
NULL,				/*	text			*/
0,				/*	mutual exclude	*/
NULL,				/*	special info	*/
1,					/*	gadget ID		*/
NULL				/*	user data		*/
};

struct Gadget rollleftgadget =
{
&rollrightgadget,
244,42,27,14,		/*	posn. and size	*/
GADGHCOMP |
GADGIMAGE,			/*	flags			*/
RELVERIFY,			/*	activation		*/
BOOLGADGET,			/*	gadget type		*/
(APTR)&rollleft,	/*	image pointer	*/
NULL,				/*	alternate image	*/
NULL,				/*	text			*/
0,				/*	mutual exclude	*/
NULL,				/*	special info	*/
2,					/*	gadget ID		*/
NULL				/*	user data		*/
};

struct Gadget yawleftgadget =
{
&rollleftgadget,
242,20,15,14,		/*	posn. and size	*/
GADGHCOMP |
GADGIMAGE,			/*	flags			*/
RELVERIFY,			/*	activation		*/
BOOLGADGET,			/*	gadget type		*/
(APTR)&yawleft,		/*	image pointer	*/
NULL,				/*	alternate image	*/
NULL,				/*	text			*/
0,				/*	mutual exclude	*/
NULL,				/*	special info	*/
3,					/*	gadget ID		*/
NULL				/*	user data		*/
};

struct Gadget yawrightgadget =
{
&yawleftgadget,
257,20,15,14,		/*	posn. and size	*/
GADGHCOMP |
GADGIMAGE,			/*	flags			*/
RELVERIFY,			/*	activation		*/
BOOLGADGET,			/*	gadget type		*/
(APTR)&yawright,	/*	image pointer	*/
NULL,				/*	alternate image	*/
NULL,				/*	text			*/
0,				/*	mutual exclude	*/
NULL,				/*	special info	*/
4,					/*	gadget ID		*/
NULL				/*	user data		*/
};

struct Gadget climbgadget =
{
&yawrightgadget,
222,41,14,15,		/*	posn. and size	*/
GADGHCOMP |
GADGIMAGE,			/*	flags			*/
RELVERIFY,			/*	activation		*/
BOOLGADGET,			/*	gadget type		*/
(APTR)&climb,		/*	image pointer	*/
NULL,				/*	alternate image	*/
NULL,				/*	text			*/
0,				/*	mutual exclude	*/
NULL,				/*	special info	*/
5,					/*	gadget ID		*/
NULL				/*	user data		*/
};


struct Gadget divegadget =
{
&climbgadget,
222,56,14,15,		/*	posn. and size	*/
GADGHCOMP |
GADGIMAGE,			/*	flags			*/
RELVERIFY,			/*	activation		*/
BOOLGADGET,			/*	gadget type		*/
(APTR)&dive,		/*	image pointer	*/
NULL,				/*	alternate image	*/
NULL,				/*	text			*/
0,				/*	mutual exclude	*/
NULL,				/*	special info	*/
6,					/*	gadget ID		*/
NULL				/*	user data		*/
};

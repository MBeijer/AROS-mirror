#!/bin/env python

import sys

sys.stdout.write('''#ifndef _SPONSORS_H_
#define _SPONSORS_H_

/*
    Copyright � 2003, The AROS Development Team. All rights reserved.
    ****** This file is automatically generated. DO NOT EDIT! *******
*/

#include <utility/tagitem.h>
#include <zune/aboutwindow.h>

struct TagItem *SPONSORS = TAGLIST
(
    SECTION
    (
        SID_NONE''')

for line in sys.stdin:
    sys.stdout.write(',\n        NAME("%s")' % line.strip())
    
print '''\n    ),
    TAG_DONE
);

#endif /* _SPONSORS_H_ */'''

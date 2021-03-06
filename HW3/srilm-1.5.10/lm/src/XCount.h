/*
 * XCount.h --
 *	Sparse integer counts stored in 2 bytes.
 *
 * Copyright (c) 1995-2006 SRI International.  All Rights Reserved.
 *
 * @(#)$Header: /home/srilm/devel/lm/src/RCS/XCount.h,v 1.12 2006/11/17 11:33:55 stolcke Exp $
 *
 */

#ifndef _XCount_h_
#define _XCount_h_

#ifdef PRE_ISO_CXX
# include <iostream.h>
#else
# include <iostream>
using namespace std;
#endif

#if !defined(_MSC_VER) && !defined(WIN32)
#include <sys/param.h>
#endif

#include "Boolean.h"

#ifdef USE_LONGLONG_COUNTS
typedef unsigned int XCountIndex;		// 4 bytes
typedef unsigned long long XCountValue;		// 8 bytes
#else
typedef unsigned short XCountIndex;		// 2 bytes
typedef unsigned long XCountValue;		// 4 bytes
#endif

#ifndef NBBY
#define NBBY	8
#endif

const unsigned XCount_Maxbits		= sizeof(XCountIndex)*NBBY-1;
const XCountIndex XCount_Maxinline	= ((XCountIndex)1 << XCount_Maxbits)-1;
const unsigned XCount_TableSize		= ((XCountIndex)1 << 15)-1;

class XCount {
public:
    XCount(XCountValue value = 0);
    XCount(const XCount &other);
    ~XCount();

    XCount & operator= (const XCount &other);
    XCount & operator+= (XCountValue value)
	{ *this = (XCountValue)*this + value; return *this; };
    XCount & operator+= (XCount &value)
	{ *this = (XCountValue)*this + (XCountValue)value; return *this; };
    XCount & operator-= (XCountValue value)
	{ *this = (XCountValue)*this - value; return *this; };
    XCount & operator-= (XCount &value)
	{ *this = (XCountValue)*this - (XCountValue)value; return *this; };

    operator XCountValue() const;

    void write(ostream &str) const;
	
private:
    XCountIndex count:XCount_Maxbits;
    Boolean indirect:1;

    static void freeXCountTableIndex(XCountIndex);
    static XCountIndex getXCountTableIndex();

    static XCountValue xcountTable[XCount_TableSize];
    static unsigned refCounts[XCount_TableSize];
    static XCountIndex freeList;
};

ostream &operator<<(ostream &str, const XCount &count);

#endif /* _XCount_h_ */


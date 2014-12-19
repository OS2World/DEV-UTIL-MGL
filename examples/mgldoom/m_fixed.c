// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//      Fixed point implementation.
//
//-----------------------------------------------------------------------------


static const char
rcsid[] = "$Id: m_bbox.c,v 1.1 1997/02/03 22:45:10 b1 Exp $";

#include "stdlib.h"

#include "doomtype.h"
#include "i_system.h"

#ifdef __GNUG__
#pragma implementation "m_fixed.h"
#endif
#include "m_fixed.h"

#ifdef _MSC_VER
#include "scitech.h"
#endif


// Fixme. __USE_C_FIXED__ or something.

/* use assembly for OS/2 & DOS, largely because it's impossible to write
   FixedMul() in C without 'long long' support     -MikeN           */

#if defined(__EMX__) || (!defined(OS2) && !defined(DOS)) || defined(_MSC_VER)

fixed_t
FixedMul
( fixed_t       a,
  fixed_t       b )
{
#if defined(_MSC_VER)
    return ((s64) a * (s64) b) >> FRACBITS;
#else
    return ((long long) a * (long long) b) >> FRACBITS;
#endif
}

#endif

//
// FixedDiv, C version.
//

fixed_t
FixedDiv
( fixed_t       a,
  fixed_t       b )
{
    if ( (abs(a)>>14) >= abs(b))
        return (a^b)<0 ? MININT : MAXINT;
    return FixedDiv2 (a,b);
}



#if defined(__EMX__) || (!defined(OS2) && !defined(DOS)) || defined(_MSC_VER)

fixed_t
FixedDiv2
( fixed_t       a,
  fixed_t       b )
{
#if 0
    long long c;
    c = ((long long)a<<16) / ((long long)b);
    return (fixed_t) c;
#endif

    double c;

    c = ((double)a) / ((double)b) * FRACUNIT;

    if (c >= 2147483648.0 || c < -2147483648.0)
        I_Error("FixedDiv: divide by zero");
    return (fixed_t) c;
}
#endif
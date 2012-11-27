/**
 * This file belongs to the FindMyPath project
 *
 * @see https://github.com/AnisB/FindMyPath
 * @author 2012-2013 Anis Benyoub <benyoub.anis@gmail.com>
 * @see The GNU Public License (GPL)
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#pragma once

#if defined(TYPES_RECURSES)
#error Recursive header files inclusion detected in TYPES.h
#else // defined(TYPES_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TYPES_RECURSES

#if !defined TYPES_h
/** Prevents repeated inclusion of headers. */
#define TYPES_h


#include <list>
#include <map>
#include <iostream>
class TPoint
{
public:
    int x;
    int y;
    double heuristic;
    double poids;
    std::list<TPoint> points;
    TPoint()
	{
	    heuristic=0.0;
	    poids=0.0;
	}
    TPoint(int anX, int aY)
	{
	    x=anX;
	    y=aY;
	    heuristic=0.0;
	    poids=0.0;
	}
    bool operator==( const TPoint &b)
	{
	    return (x == b.x)&&(y == b.y);
	}
    bool operator<( const TPoint &b)
	{
	    return x < b.x;
	}
    void debug()
	{
	    std::cout<<x<<" "<<y;
	}
};

typedef std::map<int,std::map<int,TPoint> > Graph;
#endif
#endif


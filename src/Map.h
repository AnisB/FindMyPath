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

#if defined(MAP_RECURSES)
#error Recursive header files inclusion detected in MAP.h
#else // defined(MAP_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MAP_RECURSES

#if !defined MAP_h
/** Prevents repeated inclusion of headers. */
#define MAP_h
#include "Types.h"


class TMap
{
protected:

    int myMapSizeX;
    int myMapSizeY;
    Graph myGraph;
    char ** myGridMap; 
public:
    int getSizeX()
    {
       return myMapSizeX;
    }
    int getSizeY()
    {
       return myMapSizeY;
    }
    TMap(int x, int y);

    char ** getGridMap();
    Graph getGraph();

    void GridToGraph();
	
    void printMap();
    char Wall;
    char Dirt;
};

#endif
#endif

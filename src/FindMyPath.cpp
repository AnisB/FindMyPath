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
#include "MapLoader.h"
#include <iostream>
using namespace std;
int main()
{
    MapLoader aMapLoader;
    aMapLoader.LoadMap("../Samples/map2.map");
    //aMapLoader.PrintMap();
    PathFindAStar aStar;
    aStar.setMap(aMapLoader.getMap());
    list<TPoint> solution = aStar.computePath(TPoint(0,0),TPoint(3,3));
    list<TPoint>::iterator it;
    for(it=solution.begin();it!=solution.end();it++)
    {
	cout<<it->x<<" "<<it->y<<endl;
    }	
    return 0;
}

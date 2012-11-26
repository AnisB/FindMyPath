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

#include "Map.h"

using namespace std;
TMap::TMap(int x, int y)
{
    Wall = '0';
    Dirt = '1';
    myMapSizeX=x;
    myMapSizeY=y;
    myGridMap = new  char * [myMapSizeX];
    for (int i = 0; i < myMapSizeX; i++)
    {
	myGridMap[i] = new char [myMapSizeY];
    }
    for( int i =0;i<myMapSizeX;i++)
    {
	for( int j =0;j<myMapSizeY;j++)
	{
	    myGridMap[i][j]=Wall;
	}
    }	
}

char ** TMap::getGridMap()
{
    return myGridMap;
}

Graph TMap::getGraph()
{
    return myGraph;
}

void TMap::GridToGraph()
{
    using namespace std;
    for( int i =0;i<myMapSizeX;i++)
    {
	for( int j =0;j<myMapSizeY;j++)
	{
	    if(myGridMap[i][j]!=Wall)
	    {
		TPoint newNode;
		newNode.x=i;
		newNode.y=j;
		if((i!=0) && (myGridMap[i-1][j]!=Wall) )
		{
		    TPoint a;
		    a.x=i-1;
		    a.y=j;
		    newNode.points.push_back(a);
		}
		if( (i!=(myMapSizeX-1)) && (myGridMap[i+1][j]!=Wall))
		{
		    TPoint a;
		    a.x=i+1;
		    a.y=j;
		    newNode.points.push_back(a);
		}
		if((j!=0) && (myGridMap[i][j-1]!=Wall))
		{
		    TPoint a;
		    a.x=i;
		    a.y=j-1;
		    newNode.points.push_back(a);
		}
		if( (j!=(myMapSizeY-1)) && (myGridMap[i][j+1]!=Wall))
		{
		    TPoint a;
		    a.x=i;
		    a.y=j+1;
		    newNode.points.push_back(a);
		}
		myGraph[i][j]=newNode;
	    }
	}

    }
		
		
}

void TMap::printMap()
{
    using namespace std;
    cout<<"Map format"<<endl;
    for(int i = 0;i<myMapSizeX;i++)
    {
	for(int j = 0;j<myMapSizeY;j++)
	{
	    std::cout<<(myGridMap)[i][j]<<" ";			
	}
	cout<<endl;
    }
    cout<<"Graph format"<<endl;
    Graph::iterator it;
	
    for(it=myGraph.begin();it!=myGraph.end();it++)
    {
	map<int,TPoint>::iterator it2;
	for(it2=(*it).second.begin();it2!=(*it).second.end();it2++)
	{
	    cout<<"["<<(*it).first<<", "<<(*it2).first<<"]={";
	    list<TPoint>::iterator p;
	    for(p=(*it2).second.points.begin();p!=(*it2).second.points.end();p++)
	    {
		cout<<"["<<p->x<<", "<<p->y<<"]";
	    }
	    cout<<"}"<<endl;
	}
    }
}


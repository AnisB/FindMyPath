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


struct TSolution
{
    std::list<TPoint *> points;
};

typedef std::map<int,std::map<int,TPoint> > Graph;

class TMap
{
public:
//protected:

    int myMapSizeX;
    int myMapSizeY;
    Graph myGraph;
    int ** myGridMap; 
public:
    TMap(int x, int y)
	{
	    myMapSizeX=x;
	    myMapSizeY=y;
	    myGridMap = new  int * [myMapSizeX];
	    for (int i = 0; i < myMapSizeX; i++)
	    {
		myGridMap[i] = new int [myMapSizeY];
	    }
	    for( int i =0;i<myMapSizeX;i++)
	    {
		for( int j =0;j<myMapSizeY;j++)
		{
		    myGridMap[i][j]=0;
		}
	    }	
	}

    int ** getGridMap()
	{
	    return myGridMap;
	}

    Graph getGraph()
	{
	    return myGraph;
	}

    void GridToGraph()
	{
	    using namespace std;
	    for( int i =0;i<myMapSizeX;i++)
	    {
		for( int j =0;j<myMapSizeY;j++)
		{
		    if(myGridMap[i][j]!=0)
		    {
			TPoint newNode;
			newNode.x=i;
			newNode.y=j;
			if((i!=0) && (myGridMap[i-1][j]!=0) )
			{
			    TPoint a;
			    a.x=i-1;
			    a.y=j;
			    newNode.points.push_back(a);
			}
			if( (i!=(myMapSizeX-1)) && (myGridMap[i+1][j]!=0))
			{
			    TPoint a;
			    a.x=i+1;
			    a.y=j;
			    newNode.points.push_back(a);
			}
			if((j!=0) && (myGridMap[i][j-1]!=0))
			{
			    TPoint a;
			    a.x=i;
			    a.y=j-1;
			    newNode.points.push_back(a);
			}
			if( (j!=(myMapSizeY-1)) && (myGridMap[i][j+1]!=0))
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

    void printMap()
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



};


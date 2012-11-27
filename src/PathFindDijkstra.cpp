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
#include"PathFindDijkstra.h"
#include <list>
#include <queue>
#include <map>
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef  pair<pair<int,int>,double>  PointQueue;
struct ComparePts
{
    bool operator()(PointQueue a, PointQueue b) 
     {
        return a.second > b.second; 
     }
};


typedef priority_queue<PointQueue, vector<PointQueue>, ComparePts> PriorityPts;



typedef map<pair<int,int>,pair<int,int> > Visited;
typedef map< pair<int,int>,double>  Vertex;
typedef map< pair<int,int>,pair<int,int> >  Previous;

void PathFindDijkstra::setMap(TMap * aMap)
{
    myMap=aMap;
}

void removeFromListDij(list<TPoint> & aList, TPoint aPoint)
{
    list<TPoint>::iterator it;
    for(it=aList.begin();it!=aList.end();it++)
    {
	if( ( (*it).x==aPoint.x) && ((*it).y==aPoint.y))
	{
	    aList.erase(it);
	    return;
	}
    }
}


TPoint minD(list<TPoint> aList)
{
    TPoint minimal=aList.front();
    list<TPoint>::iterator it;
    for(it=aList.begin();it!=aList.end();it++)
    {
	if(((*it).heuristic)<(minimal.heuristic))
	{
	    minimal=(*it);
	}
    }
    return minimal;
}
list<TPoint> PathFindDijkstra::computePath(TPoint  startPoint, TPoint endPoint)
/*
 1  function Dijkstra(Graph, source):
 2      for each vertex v in Graph:                                // Initializations
 3          dist[v] := infinity ;                                  // Unknown distance function from 
 4                                                                 // source to v
 5          previous[v] := undefined ;                             // Previous node in optimal path
 6      end for                                                    // from source
 7      
 8      dist[source] := 0 ;                                        // Distance from source to source
 9      Q := the set of all nodes in Graph ;                       // All nodes in the graph are
10                                                                 // unoptimized - thus are in Q
11      while Q is not empty:                                      // The main loop
12          u := vertex in Q with smallest distance in dist[] ;    // Start node in first case
13          remove u from Q ;
14          if dist[u] = infinity:
15              break ;                                            // all remaining vertices are
16          end if                                                 // inaccessible from source
17          
18          for each neighbor v of u:                              // where v has not yet been 
19                                                                 // removed from Q.
20              alt := dist[u] + dist_between(u, v) ;
21              if alt < dist[v]:                                  // Relax (u,v,a)
22                  dist[v] := alt ;
23                  previous[v] := u ;
24                  decrease-key v in Q;                           // Reorder v in the Queue
25              end if
26          end for
27      end while
28  return dist;
*/
{
  Vertex dist;
  Previous prev;
  Graph grid = myMap->getGraph();
  for(int i=0;i<myMap->getSizeX();i++)
  {
    for(int j= 0;j<myMap->getSizeY();j++)
    {
         dist[make_pair(i,j)]=10000000;
         prev[make_pair(i,j)]=make_pair(-1,-1);
    }
  }
  dist[make_pair(startPoint.x,startPoint.y)]=0;
  list<TPoint> setOfPoints;
  PriorityPts setPts;
  for(int i=0;i<myMap->getSizeX();i++)
  {
    for(int j= 0;j<myMap->getSizeY();j++)
    {
      if(grid[i][j].points.size()!=0)
      {
        setOfPoints.push_back(grid[i][j]);
        setPts.push(make_pair(make_pair(grid[i][j].x,grid[i][j].y),10000000));
      }        
    }
  }
  setPts.push(make_pair(make_pair(startPoint.x,startPoint.y),0));
  while(setPts.size()!=0)
  {
    PointQueue atemp= setPts.top();
    setPts.pop();
    TPoint a = grid[atemp.first.first][atemp.first.second];
    if(dist[make_pair(a.x,a.y)]==-1)
    {
    }
    else
    {
      list<TPoint>::iterator that;
      for(that=a.points.begin();that!=a.points.end();that++)
      {
        double alt = dist[make_pair(a.x,a.y)]+1;
        if(alt<dist[make_pair((*that).x,(*that).y)])
	{
          dist[make_pair((*that).x,(*that).y)]=alt;
	  prev[make_pair((*that).x,(*that).y)]=make_pair(a.x,a.y);
          setPts.push(make_pair(make_pair((*that).x,(*that).y),alt));
	}
      }
    }
  }
  list<TPoint> Solution;
  pair<int,int> temp;
  temp.first=endPoint.x;
  temp.second=endPoint.y;
  while((temp.first!=startPoint.x)||(temp.second!=startPoint.y))
  {
    TPoint newP;
    pair<int,int> aP=prev[make_pair(temp.first,temp.second)];
    newP.x = aP.first;
    newP.y = aP.second;
    Solution.push_front(newP);
    temp=aP;
  }
  return Solution;
  
}
void PathFindDijkstra::getPath()
{
}

void PathFindDijkstra::computeHeuristics(TPoint goal)
{
    list<TPoint>::iterator it;
    for(it=myOpenList.begin();it!=myOpenList.end();it++)
    {
	if(((*it).x!=goal.x)||((*it).y!=goal.y))	
	{
	    unsigned int diffX =abs((*it).x-goal.x);
	    unsigned int diffY =abs((*it).y-goal.y);
	    (*it).heuristic=sqrt(diffX*diffX+diffY*diffY);
	}
	else
	{
	    (*it).heuristic=0.0f;		
	}
    }
	
}

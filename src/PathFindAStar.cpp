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
#include"PathFindAStar.h"
#include <list>
#include <map>
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef map<pair<int,int>,pair<int,int> > Visited;





double computeHeuristic(TPoint  a, TPoint b)
{
    if((a.x!=b.x)||(a.y!=b.y))	
    {
	unsigned int diffX =abs(a.x-b.x);
	unsigned int diffY =abs(a.y-b.y);
	return sqrt(diffX*diffX+diffY*diffY);

    }
    else
    {
	return 0.0f;		
    }
}

bool isOrdered(list<TPoint> laListe)
{

  double tampon = 0.0;
  list<TPoint>::iterator it;
  laListe.reverse();
  for(it=laListe.begin();it!=laListe.end();it++)
  {
    if(it->heuristic>tampon)
    {
	tampon=it->heuristic;
    }
    else
    {
	return false;
    }
  }
  return true;

}

void orderNeibs(list<TPoint> & liste, TPoint a)
{

  multimap<double,TPoint> dict;
   list<TPoint>::iterator it;
  multimap<double,TPoint>::iterator mp;
  for(it=liste.begin();it!=liste.end();it++)
  {
    it->heuristic=computeHeuristic(*it,a);
  }
  for(it=liste.begin();it!=liste.end();it++)
  {
    dict.insert(pair<double,TPoint>(it->heuristic,(*it)));
  }
  liste.clear();
  for(mp=dict.begin();mp!=dict.end();mp++)
  {
    liste.push_back(mp->second);
  }
  liste.reverse();

}


TPoint minHeuristic(list<TPoint> aList)
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
void removeFromList(list<TPoint> & aList, TPoint aPoint)
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

bool belongs(list<TPoint> & aList, TPoint aPoint)
{
    list<TPoint>::iterator it;
    for(it=aList.begin();it!=aList.end();it++)
    {
	if( ( (*it).x==aPoint.x) && ((*it).y==aPoint.y))
	{
	    return true;
	}
    }
    return false;
}

void PathFindAStar::setMap(TMap * aMap)
{
    myMap=aMap;
}


list<TPoint> reconstruire(Visited aMap,TPoint a)
{
     
    if (aMap.find(make_pair(a.x,a.y))!=aMap.end())
    {	
	TPoint z(aMap[make_pair(a.x,a.y)].first,aMap[make_pair(a.x,a.y)].second);
	list<TPoint> p = reconstruire(aMap, z);
	p.push_back(a);
	return p;
    }     
    else
    { list<TPoint> z;
	z.push_back(a);
	return z;
    }
}

list<TPoint> PathFindAStar::computePath(TPoint  startPoint, TPoint endPoint)
{
    TPoint current;
    myCloseList.clear();
    myOpenList.push_back(startPoint);
    computeHeuristics(endPoint);
    Visited myNavigated;
    myNavigated.clear();
    myMap->getGraph()[startPoint.x][startPoint.y].poids=0;
    myMap->getGraph()[startPoint.x][startPoint.y].heuristic=
	myMap->getGraph()[startPoint.x][startPoint.y].poids+computeHeuristic(startPoint,endPoint);
    while(myOpenList.size()!=0)
    {
	current=minHeuristic(myOpenList);
	if((current.x==endPoint.x) && (current.y==endPoint.y))
	{
	    return reconstruire(myNavigated,endPoint);
	}
	removeFromList(myOpenList,current);
	myCloseList.push_front(current);
	list<TPoint> neibs= myMap->getGraph()[current.x][current.y].points;
	list<TPoint>::iterator p;
        orderNeibs(neibs,endPoint);
	for(p=neibs.begin();p!=neibs.end();p++)
	{
		
	    if(belongs(myCloseList,*p))
	    {
	    }
	    else
	    {
		int tentative=myMap->getGraph()[current.x][current.y].poids+1;
				
		if((!belongs(myOpenList,*p))||(tentative<=myMap->getGraph()[(*p).x][(*p).y].poids))
		{


		    myNavigated[make_pair((*p).x,(*p).y)]=make_pair(current.x,current.y);
		    myMap->getGraph()[(*p).x][(*p).y].poids=tentative;
		    myMap->getGraph()[(*p).x][(*p).y].heuristic=tentative+computeHeuristic((*p),endPoint);
		    if(!belongs(myOpenList,*p))
		    {
			myOpenList.push_front(*p);	
		    }

		}
			
	    }
		
	}
    }
    list<TPoint> b;
    return b;

	
}
void PathFindAStar::getPath()
{
}

void PathFindAStar::computeHeuristics(TPoint goal)
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

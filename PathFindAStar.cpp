
#include"PathFindAStar.h"

void PathFindAStar::setMap(TMap * aMap)
{
	myMap=aMap;
}
void PathFindAStar::computePath(TPoint * startPoint, TPoint * endPoint)
{
	myCloseList.clear();
	myOpenList=myMap.getPoints();
	computeHeuristics(goal);
	
}
void PathFindAStar::getPath()
{
}

void PathFindAStar::computeHeuristics(TPoint * goal)
{
	list<TPoint *>::iterator it;
	for(it=myOpenList.begin();it!=myOpenList.end();it++)
	{
		if(((*it)->x!=goal->x)&&((*it)->y!=goal->y))	
		{
			unsigned int diffX =abs((*it)->x-goal->x);
			unsigned int diffY =abs((*it)->y-goal->y);
			(*it)->heuristic=sqrt(diffX*diffX+diffY*diffY);
		}
		else
		{
			(*it)->heuristic=0.0f;		
		}
	}
	
}

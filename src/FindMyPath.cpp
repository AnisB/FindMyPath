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

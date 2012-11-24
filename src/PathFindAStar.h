#include "Types.h"
class PathFindAStar
{
	protected:
		TMap * myMap;
		TSolution * mySolution;
		std::list<TPoint> myCloseList;
		std::list<TPoint> myOpenList;

	public:
	
		void setMap(TMap * aMap);
		std::list<TPoint>  computePath(TPoint startPoint, TPoint endPoint);
		void getPath();
		void computeHeuristics(TPoint  goal);
};

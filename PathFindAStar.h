
#include "Types.h"
class PathFindAStar
{
	protected:
		TMap * myMap;
		TSolution * mySolution;
		std::list<TPoint*> myCloseSet;
		std::list<TPoint*> myOpenSet;
	public:
	
		void setMap(TMap * aMap);
		void computePath();
		void getPath();
		void computeHeuristics(TPoint * goal);
}

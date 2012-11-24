

#include "PathFindAStar.h"
#include <iostream>
#include <vector>

class MapLoader
{
	protected:
		TMap * myMap;
	public:
		MapLoader();
		virtual ~MapLoader();
		TMap*	LoadMap(std::string fileName);
		std::vector<std::string> split ( std::string &chaine, char c );
		void PrintMap();
		TMap * getMap();

};

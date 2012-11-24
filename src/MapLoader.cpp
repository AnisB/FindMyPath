#include "MapLoader.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

MapLoader::MapLoader()
{
	//Nothing to do
}

MapLoader::~MapLoader()
{
	//Nothing to do
}



int StringToNumber ( const string Text )
{                              
	stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}


vector<string> MapLoader::split ( string &chaine, char c )
{
	int size = chaine.size();
	int r = 0;
	vector<string> v;
	for (int i = 0; i < size; i++)
	{
		if (chaine[i] == c)
		{
			v.push_back(chaine.substr(r, i - r));
			r = i + 1;
		}
	}
	v.push_back(chaine.substr(r, size - r));
	return v;
}

TMap*	MapLoader::LoadMap(std::string fileName)
{

	string line;
	ifstream myfile (fileName.c_str());
 	getline (myfile,line);
	int nL=StringToNumber (line );
 	getline (myfile,line);
	int nC=StringToNumber (line );  

	myMap = new TMap(nL,nC);
	int ** map =myMap->getGridMap();
	if (myfile.is_open())
	{
		int l=0;
		while ( myfile.good() && l<nL )
	  	{
	      		getline (myfile,line);
	      		std::vector<std::string> aLine = split(line,' ');
			for(int i=0;i<nC;i++)
			{
				int x=StringToNumber(aLine[i]);
				map[l][i]=x;
			}

			l++;
	    	}

	    	myfile.close();
		
	}
	else
	{
		cout<<"Problème d'ouverture fichier"<<endl;
	}
	myMap->GridToGraph();
	return myMap;
		
}

void MapLoader::PrintMap()
{
	myMap->printMap();
}

TMap * MapLoader::getMap()
{
	return myMap;
}

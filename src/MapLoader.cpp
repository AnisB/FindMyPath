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

    if(line=="B")
    {
    	    getline (myfile,line);
	    int nL=StringToNumber (line );
	    getline (myfile,line);
	    int nC=StringToNumber (line );  

	    myMap = new TMap(nL,nC);
	    char ** map =myMap->getGridMap();
		int l=0;
		while ( myfile.good() && l<nL )
		{
		    getline (myfile,line);
		    std::vector<std::string> aLine = split(line,' ');
		    for(int i=0;i<nC;i++)
		    {
		
			map[l][i]=aLine[i][0];
		    }

		    l++;
		}

		myfile.close();
		
    }
    else if(line=="A")
    {
	    getline (myfile,line);
	    int nL=StringToNumber (line );
	    getline (myfile,line);
	    int nC=StringToNumber (line );  

	    myMap = new TMap(nL,nC);
	    char ** map =myMap->getGridMap();
		int l=0;
		while ( myfile.good() && l<nL )
		{
		    getline (myfile,line);
	
		    for(int i=0;i<nC;i++)
		    {
		
			map[l][i]=line[i];
		    }

		    l++;
		}

		myfile.close();
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

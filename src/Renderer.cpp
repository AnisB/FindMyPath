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

#include "Renderer.h"
#include "PathFindDijkstra.h"
using namespace sf;
using namespace std;
Renderer::Renderer()
{
  myApp = new RenderWindow(VideoMode(800, 800, 32), "Find my path");
  if (!myImage.LoadFromFile("img/image.png"))  
  {
    cout<<"Problem"<<endl;
  }
  if (!myImage2.LoadFromFile("img/dirt1.png"))  
  {
    cout<<"Problem"<<endl;
  }
}
Renderer::~Renderer()
{
  delete myApp;
}

void Renderer::render()
{
  while (myApp->IsOpened())
    {
        Event event;

        while (myApp->GetEvent(event))
        {
            if (event.Type == Event::Closed)
                myApp->Close();
        }

        // Remplissage de l'écran (couleur noire par défaut)
        myApp->Clear();

        drawMap();

        // Affichage de la fenêtre à l'écran
        myApp->Display();
    }
}
void Renderer::drawMap()
{
  char ** map=myMap->getGridMap();
  int nL = myMap->getSizeX();
  int nC = myMap->getSizeY();
  int cx = 800/nL+1 ;
  int cy = 800/nC+1 ;
  for(int i=0;i<nL;i++)
  {
     for(int j=0;j<nC;j++)
     {
	Shape carre;
        if(map[i][j]==myMap->Wall)
	{
	   sf::Sprite Sprite2;
	   Sprite2.SetImage(myImage);
	   Sprite2.SetPosition(cx*i+1, cy*j+1);
	   Sprite2.SetScale((double)(cx-2)*1.0/myImage.GetWidth(),(double)(cy-2)*1.0/myImage.GetHeight());
	   myApp->Draw(Sprite2);
	}
	else if(map[i][j]==myMap->Dirt)
	{
	   sf::Sprite Sprite2;
	   Sprite2.SetImage(myImage2);
	   Sprite2.SetPosition(cx*i, cy*j);
	   Sprite2.SetScale((double)(cx)*1.0/myImage2.GetWidth(),(double)(cy)*1.0/myImage2.GetHeight());
	   myApp->Draw(Sprite2);
	}
	myApp->Draw(carre);
     }
  }
  std::list<TPoint>::iterator it=path.begin();
    Shape begin;
    begin.AddPoint((cx)*(*it).x+1, (cy)*(*it).y+1, Color(20,150,20), Color(255,255,255));
    begin.AddPoint((cx)*(*it).x+1, (cy)*(*it).y+cy-1, Color(20,150,20), Color(255,255,255));
    begin.AddPoint((cx)*(*it).x+cx-1, (cy)*(*it).y+cy-1, Color(20,150,20), Color(255,255,255));
    begin.AddPoint((cx)*(*it).x+cx-1, (cy)*(*it).y+1, Color(20,150,20), Color(255,255,255));
    begin.EnableFill(true); // Remplissage activé
    begin.EnableOutline(true); // Bordures activées
    begin.SetOutlineWidth(1); // Bordures de taille 20 pixels
    myApp->Draw(begin);
    it++;
  for(;it!=path.end();it++)
  {
    Shape carre;
    carre.AddPoint((cx)*(*it).x+1, (cy)*(*it).y+1, Color(60,20,200), Color(255,255,255));
    carre.AddPoint((cx)*(*it).x+1, (cy)*(*it).y+cy-1, Color(60,20,200), Color(255,255,255));
    carre.AddPoint((cx)*(*it).x+cx-1, (cy)*(*it).y+cy-1, Color(260,20,200), Color(255,255,255));
    carre.AddPoint((cx)*(*it).x+cx-1, (cy)*(*it).y+1, Color(60,20,200), Color(255,255,255));
    carre.EnableFill(true); // Remplissage activé
    carre.EnableOutline(true); // Bordures activées
    carre.SetOutlineWidth(1); // Bordures de taille 20 pixels
    myApp->Draw(carre);
  }
}
void Renderer::getMap(std::string aFileName)
{
    MapLoader aMapLoader;
    aMapLoader.LoadMap(aFileName);
    myMap=aMapLoader.getMap();
}

void Renderer::AStar(int x, int y , int x1, int y1)
{
  PathFindAStar aPath;
  aPath.setMap(myMap);
  path=aPath.computePath(TPoint(x,y),TPoint(x1,y1));
}

void Renderer::Dijkstra(int x, int y , int x1, int y1)
{
  PathFindDijkstra aPath;
  aPath.setMap(myMap);
  path=aPath.computePath(TPoint(x,y),TPoint(x1,y1));
}

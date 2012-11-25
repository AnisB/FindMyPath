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
using namespace sf;
Renderer::Renderer()
{
  myApp = new RenderWindow(VideoMode(800, 600, 32), "Find my path");
   
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
  int cx = 800/nL -1;
  int cy = 600/nC ;
  for(int i=0;i<nL;i++)
  {
     for(int j=0;j<nC;j++)
     {
	Shape carre;
        if(map[i][j]==Wall)
	{
		carre.AddPoint(cx*i+0, cy*j+0, Color(0,0,0), Color(255,255,255));
		carre.AddPoint(cx*i+0, cy*j+cy, Color(0,0,0), Color(255,255,255));
		carre.AddPoint(cx*i+cx, cy*j+cy, Color(0,0,0), Color(255,255,255));
		carre.AddPoint(cx*i+cx, cy*j+0, Color(0,0,0), Color(255,255,255));
		carre.EnableFill(true); // Remplissage activé
    		carre.EnableOutline(true); // Bordures activées
    		carre.SetOutlineWidth(1); // Bordures de taille 20 pixels
	}
	else if(map[i][j]==Dirt)
	{
		carre.AddPoint(cx*i+0, cy*j+0, Color(255, 90, 20), Color(255,255,255));
		carre.AddPoint(cx*i+0, cy*j+cy, Color(255, 90, 20), Color(255,255,255));
		carre.AddPoint(cx*i+cx, cy*j+cy, Color(255, 90, 20), Color(255,255,255));
		carre.AddPoint(cx*i+cx, cy*j+0, Color(255, 90, 20), Color(255,255,255));
		carre.EnableFill(true); // Remplissage activé
		carre.EnableOutline(true); // Bordures activées
		carre.SetOutlineWidth(1); // Bordures de taille 20 pixels
	}
	myApp->Draw(carre);
     }
  }
  std::list<TPoint>::iterator it=path.begin();
    Shape begin;
    begin.AddPoint(cx*(*it).x+0, cy*(*it).y+0, Color(20,150,20), Color(255,255,255));
    begin.AddPoint(cx*(*it).x+0, cy*(*it).y+cy, Color(20,150,20), Color(255,255,255));
    begin.AddPoint(cx*(*it).x+cx, cy*(*it).y+cy, Color(20,150,20), Color(255,255,255));
    begin.AddPoint(cx*(*it).x+cx, cy*(*it).y+0, Color(20,150,20), Color(255,255,255));
    begin.EnableFill(true); // Remplissage activé
    begin.EnableOutline(true); // Bordures activées
    begin.SetOutlineWidth(1); // Bordures de taille 20 pixels
    myApp->Draw(begin);
    it++;
  for(;it!=path.end();it++)
  {
    Shape carre;
    carre.AddPoint(cx*(*it).x+0, cy*(*it).y+0, Color(60,20,200), Color(255,255,255));
    carre.AddPoint(cx*(*it).x+0, cy*(*it).y+cy, Color(60,20,200), Color(255,255,255));
    carre.AddPoint(cx*(*it).x+cx, cy*(*it).y+cy, Color(260,20,200), Color(255,255,255));
    carre.AddPoint(cx*(*it).x+cx, cy*(*it).y+0, Color(60,20,200), Color(255,255,255));
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

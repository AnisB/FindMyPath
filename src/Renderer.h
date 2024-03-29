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
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapLoader.h"
class Renderer
{
protected:
    sf::RenderWindow * myApp;
    TMap * myMap;
    std::list<TPoint> path;
    sf::Image myImage;
    sf::Image myImage2;
public:
    Renderer();
    ~Renderer();
    void render();
    void drawMap();
    void getMap(std::string aFileName);
    void printMap();
    void AStar(int x, int y , int x1, int y1);
    void Dijkstra(int x, int y , int x1, int y1);
};

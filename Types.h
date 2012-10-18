


#include<list>

typedef struct T_Point
{
	unsigned int x;
	unsigned int y;
	double heuristic;
	std::list<T_Point *>
} TPoint;


typedef struct T_Solution
{
	std::list<T_Point *>
} TPoint;



class TMap
{
protected:
	unsigned int myMapSizeX;
	unsigned int myMapSizeY;
	std::list<TPoint*> myPoints;
public:
	TMap()
	{
		myMapSizeX=0;
		myMapSizeY=0;	
	}
	void addPoint(TPoint * aPoint)
	{
		if(myMapSizeX <= aPoint->x)
		{
			myMapSizeX=aPoint->x+1;
		}
		if(myMapSizeY <= aPoint->y)
		{
			myMapSizeY=aPoint->y+1;
		}
	}
	void setMaxX(unsigned int aX)
	{
		myMapSizeX=aX+1;
	}
	void setMaxY(unsigned int anY)
	{
		myMapSizeY=anY+1;
	}
	std::list<TPoint*> & getPoints()
	{
		return myPoints
	}


};


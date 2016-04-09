#include <time.h>
#include <iostream>
#include "Methods.h"

class Flowers
{
public:
	Methods m;
public:
	int polen = 7;
	bool ripe = false;

	void setValues(const int input1,  const bool input2)
	{
		polen = input1;
		
		ripe = input2;
	}

	//methos will be called every time the player presses SPACE
	void harvest()
	{
		if (polen > 1)
		{
			polen--; 
			ripe = true;
			
		}
		else
		{
			
			ripe = false;
		}
		
		
	}

};

class Bees
{
private:
	int score = 0;
	int hp = 10;
public:
	void add_points()
	{
		score++;
	}
	int getPoints()
	{
		return score;
	}
	void setPoints(const int x)
	{
		score = x;
	}

	void add_hp()
	{
		hp++;
	}
	int get_hp()
	{
		return hp;
	}
	void set_hp(const int y)
	{
		hp = y;
	}
	

};


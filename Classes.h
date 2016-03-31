#include <time.h>
#include <iostream>
#include "Methods.h"

class Flowers
{
private:
	Methods m;
public:
	int polen;
	int harvest_time;
	bool ripe = false;

	void setValues(int input1,  bool input3)
	{
		polen = input1;
		harvest_time = m.random_n_generator(3, 10);
		ripe = input3;
	}

	//methos will be called every time the player presses SPACE
	void harvest()
	{
		if (polen > 1)
		{
			polen--; 
			ripe = true;
			std::cout << "polen harvested! " << polen << " left!\n";
		}
		else
		{
			std::cout << "Empty!\n";
			ripe = false;
		}
		
		
	}

	/*int random_timer()
	{
		int seed = time(NULL);
		srand(seed);
		harvest_time = rand() % 10 + 3;
		return harvest_time;
	}*/
	
	

};

class Bees
{
private:
	int score = 0;
public:
	void add_points()
	{
		score++;
	}
	int getPoints()
	{
		return score;
	}

};


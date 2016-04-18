#include <time.h>
#include <iostream>

/*This class provides the game with three very usefeul methods:
random_n_generator(): yields a random number given a certain start point 
and total number of integers to be picked from. 

timer_check(): once the player has given a certain timer- in seconds- this method will 
calculate if the time is up and return the amount of time left, so when it is equal to 
zero or a certain value the code will trigger a response in the game.

reset_timer(): resets the timer so it can be used again

The class will have many different instances in the code, so different timers can be 
handled at the same time, and different random numbers generated, for example.
*/

class Methods
{
public:
	int check = 0;
	int time_left = 0;
	int start = 0;
	int timeLimit = 0;

	int random_n_generator(const int start, const int total)
	{
		srand(time(NULL));
		int result = rand() % total + start;
		
		return result;
	}

	int timer_check()
	{

		int total_seconds = 0;

		int end = 0;

		check += 1;

		//If it is the first time accessing the function, define the timer start instant
		if (check == 1)
		{

			start = time(NULL);

		}

		end = time(NULL);

		//calculates the difference between the instant it started and the most updated time
		total_seconds = difftime(end, start);

		time_left = timeLimit - total_seconds;

		return time_left;
	}

	void reset_timer()
	{
		check = 0;
	}

};
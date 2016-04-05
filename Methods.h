#include <time.h>
#include <iostream>


class Methods
{
public:
	int check = 0;
	int time_left = 0;
	int start = 0;
	int timeLimit = 0;

	int random_n_generator(int start, int end)
	{
		srand(time(NULL));
		int result = rand() % end + start;
		
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
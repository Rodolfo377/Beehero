#include <time.h>
#include <iostream>

int check = 0;
int time_left = 60;

int random_n_generator(int start, int end)
{
	srand(time(NULL));
	int result = rand() % end + start;
	std::cout << "result: " << result << std::endl;
	return result;
}

bool timer_check()
{
	bool game_over = false;
	
	int total_seconds = 0;
	int beginning;
	int end;

	check += 1;

	//If it is the first time accessing the function, define the timer start instant
	if (check == 1)
	{
		beginning = time(NULL);

	}

	end = time(NULL);

	//calculates the difference between the instant it started and the most updated time
	total_seconds = difftime(end, beginning);
	
	time_left = 60 - total_seconds;

	if (time_left <= 0)
	{
		game_over = true;
	}
	
	return game_over;
}
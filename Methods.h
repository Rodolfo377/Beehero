#include <time.h>
#include <iostream>

int random_n_generator(int start, int end)
{
	srand(time(NULL));
	int result = rand() % end + start;
	std::cout << "result: " << result << std::endl;
	return result;
}
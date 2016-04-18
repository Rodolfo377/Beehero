#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>

#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif
//R_SIZE stands for "Ranking Size", which is the amount of elements the array topScore[] will have
#ifndef R_SIZE
#define R_SIZE 5
#endif




class Ranking:public Window
{

public:Ranking(int newScore)
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ranking");
	window.setFramerateLimit(60);

	int topScore[R_SIZE] = {10000, 5000, 2500, 1250, 625};
	int* updated_Top_Score;
	int i = 0;

	updated_Top_Score = update_score(newScore, topScore);

	std::cout << "Ranking\n\n";
	for (int j = 0; j < R_SIZE; j++)
	{
		std::cout  << j + 1 << " - " << updated_Top_Score[j] << "\n";
	}

	while (window.isOpen())
	{
		
		sf::Event event;
		//Events
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Logic
		//Rendering
		window.clear();
		
		window.display();
	}
}
private:
	int* update_score(int newScore, int *score_array)
	{
		//Will store the values of the score_array pointer (elements of the array entered as a parameter)
		int copy_original[R_SIZE];

		//copies the values of one array to the other
		for (int i = 0; i < R_SIZE; i++)
		*(copy_original+i) = *(score_array+i);

		int i = 0;
		int index = 0;

		for (int i = 0; i < R_SIZE; i++)
			std::cout << copy_original[i] << "\n";
		//Loop looks for the first element of the original array that is lower than the newest 
		//score and save that element's position as 'index', then it replaces the original element by the newest at the 
		//'index' value (that is, the first replacement already takes place in this loop)
			while (i < R_SIZE)
			{
				std::cout << "first loop\n";
				if (newScore > *(score_array + i))
				{
					index = i;
					//Makes sure the next loop wont happen
					i = 1000;
					score_array[index] = newScore;
				}
				i++;
			}

			for (int i = 0; i < R_SIZE; i++)
				std::cout << score_array[i] << "\n";
			for (int i = 0; i < R_SIZE; i++)
				std::cout << copy_original[i] << "\n";

			//This loop updates the rest of the high scores array, if the new score is not the least among the top scores
			while (index < R_SIZE - 1)
			{
				std::cout << "second  loop\n";

				score_array[index + 1] = copy_original[index];
				for (int i = 0; i < R_SIZE; i++)
					std::cout << score_array[i] << "\n\n";

				for (int i = 0; i < R_SIZE; i++)
					std::cout << copy_original[i] << "\n";
				std::cout << "\n\n";
				index++;
			}
			for (int i = 0; i < R_SIZE; i++)
				std::cout << score_array[i] << "\n";

			return score_array;
		
	}
	   
};
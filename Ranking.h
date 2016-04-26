#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
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





class Ranking:public StandartWindow
{

public:Ranking(int newScore)
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ranking");
	window.setFramerateLimit(60);

	
	std::string ranking[R_SIZE];

	int previous_Top_Score[R_SIZE];

	int updated_Top_Score[R_SIZE];

	
	sf::Text bestScores[R_SIZE];
	sf::Text title;		

	title = write("Ranking", (double)WIDTH/3, (double)HEIGHT*0.05);
	title.setCharacterSize(30);

	loadImage();

	read_ranking_file(ranking);	
	translate_str_to_int(ranking, previous_Top_Score);

	for (int i = 0; i < R_SIZE; i++)
		updated_Top_Score[i] = previous_Top_Score[i];

	update_score(newScore, updated_Top_Score);

	translate_int_to_str(updated_Top_Score, ranking);

	update_ranking_file(ranking);
	
	std::string pos[5];

	 pos[0] = "1st : ";
	 pos[1] = "2nd : ";
	 pos[2] = "3rd : ";
	 pos[3] = "4th : ";
	 pos[4] = "5th : ";


	//Assigning the updated strings as arguments of a Text object to be displayed on the screen
	for (int k = 0; k < R_SIZE; k++)
		bestScores[k] = write(pos[k]+ranking[k], WIDTH / 3, HEIGHT*0.15*(k + 1));

	blink.timeLimit = 2;
	pressKey = write("PRESS ANY KEY TO LEAVE", WIDTH / 5, HEIGHT*0.85);
	pressKey.setCharacterSize(25);
	
	sf::Event event;
	while (window.isOpen())
	{
		
		
		//Events
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				window.close();
			}
		}
		//Logic
		blink_item();
		//Rendering
		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < R_SIZE; i++)
			window.draw(bestScores[i]);

		if (visible == true)
		{
			window.draw(pressKey);
		}

		window.display();
	}
}
private:
	/*The method update_score() will determine how the score ranking will be altered after taking into
	account the player's lastest try.*/
	void update_score(int newScore, int *score_array)
	{
		//Will store the values of the score_array pointer (elements of the array entered as a parameter)
		int copy_original[R_SIZE];

		//copies the values of one array to the other
		for (int i = 0; i < R_SIZE; i++)
			*(copy_original + i) = *(score_array + i);

		int i = 0;
		int index = 0;

	

		//Loop looks for the first element of the original array that is lower than the newest score 
		//and saves that element's position as 'index', then it replaces the original element
		//by the newest at the 'index' value (that is, the first replacement already takes place in this loop)

		while (i < R_SIZE)
		{
			
			if (newScore > *(score_array + i))
			{
				index = i;
				//Makes sure the next loop wont happen
				i = 1000;
				score_array[index] = newScore;
			}

			i++;
		}	

		//If the new score is actually greater than at least the last on the top 5
		if (newScore > *(score_array + (R_SIZE - 1)))
		{
			//This loop updates the rest of the high scores array, if the new score is not the least among the top scores
			while (index < R_SIZE - 1)
			{
				score_array[index + 1] = copy_original[index];
				
				index++;
			}

		}
		
	}

	/*The code of the function below 'read_ranking_file()' was adaptded from 
	http://www.cplusplus.com/doc/tutorial/files/ */

	//The method read_ranking_file() is responsible for reading the previous top scores into the ranking.txt file
	void read_ranking_file(std::string* input)
	{
		int i = 0;
		
			std::string line;
			std::ifstream myfile("Ranking/ranking.txt");

			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					*(input+i) = line;
					i++;
				}
				myfile.close();
			}

			else { std::cout << "Unable to open file"; }

	}

	/*The code of the function below 'update_ranking_file()' was adaptded from
	http://www.cplusplus.com/doc/tutorial/files/ */

	//The method update_ranking_file() is responsible for writing the updated top scores into the ranking.txt file
	void update_ranking_file(std::string *bestScores)
	{
		
		std::ofstream myfile("Ranking/ranking.txt");
		if (myfile.is_open())
		{
			for (int counter = 0; counter < R_SIZE; counter++)
			{
				myfile << *(bestScores + counter) << "\n";
				
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";
		
	}

	void translate_str_to_int(std::string *top5, int*best5)
	{
		std::string::size_type sz;   // alias of size_t

		for (int i = 0; i < R_SIZE; i++)
			*(best5 + i) = std::stoi(*(top5+i), &sz);

		
	}
	void translate_int_to_str(int*best5, std::string *top5)
	{
		
		for (int i = 0; i < R_SIZE; i++)
		*(top5+i) = convert("", *(best5 + i));
	}
};
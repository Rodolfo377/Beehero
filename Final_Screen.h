#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif

/*Class 'Winter' is responsible for showing the player's performance in an interactive way:
Depending on the player's overall score (calculated by the sum of the 3 rounds' play),
A certain number of bee hives will appear on the tree, according to the following criteria:

Score Band ---- Bee Hives
0				0
1-4999			1
5000-9999		2
10000-14999		3
15000-19999		4
20000-24999		5
25000-			6

So, the number of bee hives work as a manner of grading of the player's game result, from 1 to 6
(and zero only if the player was not able to survive at least one round and harvest at least one flower).
*/
class Winter
{
	sf::Texture hive[7];
	sf::RectangleShape canvas;

public:
	Winter(const int final_score)
	{
		
			sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Results");
			window.setFramerateLimit(60);

			sf::Event event;

			canvas.setSize(sf::Vector2f(WIDTH, HEIGHT));
			canvas.setPosition(0, 0);

			loadImages();
			chooseImage(final_score);

			std::cout << "final score: "<<final_score << "\n";

			while (window.isOpen())
			{
				
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				window.clear();
				window.draw(canvas);
				window.display();
			}//while window is open		
	}//class constructor

private:
	//loads all the possible background images given any result from the player's performance
	void loadImages()
	{
		if (hive[0].loadFromFile("Images/Scenario/Winter/Winter_Tree.png") == 0)
		{
			std::cout << "'Winter_Tree.png' not found...\n";
		}
		if (hive[1].loadFromFile("Images/Scenario/Winter/Winter_Tree_1.png") == 0)
		{
			std::cout << "'Winter_Tree_1.png' not found...\n";
		}
		if (hive[2].loadFromFile("Images/Scenario/Winter/Winter_Tree_2.png") == 0)
		{
			std::cout << "'Winter_Tree_2.png' not found...\n";
		}
		if (hive[3].loadFromFile("Images/Scenario/Winter/Winter_Tree_3.png") == 0)
		{
			std::cout << "'Winter_Tree_3.png' not found...\n";
		}
		if (hive[4].loadFromFile("Images/Scenario/Winter/Winter_Tree_4.png") == 0)
		{
			std::cout << "'Winter_Tree_4.png' not found...\n";
		}
		if (hive[5].loadFromFile("Images/Scenario/Winter/Winter_Tree_5.png") == 0)
		{
			std::cout << "'Winter_Tree_5.png' not found...\n";
		}
		if (hive[6].loadFromFile("Images/Scenario/Winter/Winter_Tree_6.png") == 0)
		{
			std::cout << "'Winter_Tree_6.png' not found...\n";
		}
	}

	//chooses proper background image based on the final score 
	void chooseImage(const int final_score)
	{
		

		if (final_score == 0)
		{
			std::cout << " 0\n";
			canvas.setTexture(&hive[0]);
		}
		else if (final_score > 0 && final_score < 5000)
			canvas.setTexture(&hive[1]);
		else if (final_score >= 5000 && final_score < 10000)
		{
			std::cout << "Entre 5k e 10k\n";
			canvas.setTexture(&hive[2]);
		}
		else if (final_score >= 10000 && final_score < 15000)
		{
			std::cout << "Entre 10k e 15k\n";
			canvas.setTexture(&hive[3]);
		}
		else if (final_score >= 15000 && final_score < 20000)
			canvas.setTexture(&hive[4]);
		else if (final_score >= 20000 && final_score < 25000)
			canvas.setTexture(&hive[5]);
		else if (final_score >= 25000)
			canvas.setTexture(&hive[6]);
	}
};
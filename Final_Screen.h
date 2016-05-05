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
class Winter : public StandartWindow
{
	sf::Texture hive[7];
	sf::RectangleShape canvas;
	sf::SoundBuffer collectBuffer;
	sf::Sound collect;
	sf::Text roundText[3];
	sf::Text totalHoney;
	sf::Text thanks;
	sf::Text presskey;

public:
	Winter(const int * const scores)
	{
		
			sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Results");
			window.setFramerateLimit(60);

			sf::Event event;

			canvas.setSize(sf::Vector2f(WIDTH, HEIGHT));
			canvas.setPosition(0, 0);

			if (collectBuffer.loadFromFile("Sound/polen_pickup.wav") == 0)
			{
				std::cout << "'polen_pickup.wav' not found...\n";
			}

			int final_score = 0;
			int round_score = 0;
			int round_counter = 0;
			
			collect.setBuffer(collectBuffer);
			collect.setVolume(40);

			loadImages();
			
			//the variable 'counting' will help the code skip the statements that deal with drawing the proper number of hives on
			//the screen after it has been done. 
			bool counting = true;
			
			chooseImage(final_score);

			//round_counter is a variable that will help making the final sum of the scores (the one visually displayed) 
			//quicker to the user.
			
			thanks = write("'Thanks for playing!' - Rodolfo", 350, 500);

			pressKey = write("PRESS ANY KEY TO LEAVE", WIDTH / 5, HEIGHT - 50);
			pressKey.setCharacterSize(25);
			blink.timeLimit = 2;

			while (window.isOpen())
			{
				
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();

					if (event.type == sf::Event::KeyPressed)
					{
						window.close();
					}
				}

				if (counting)
				{

				window.clear();
				window.draw(canvas);
				window.display();

				
					for (int i = 0; i < 3; i++)
					{
						

						

						while (round_counter < *(scores + i))
						{

							if (round_counter + 100 > *(scores + i))
							{
								round_counter += 1;
								collect.play();
							}

							else
							{
								round_counter += 50;
								collect.play();
							}

							//If the code is now counting the second or the third rounds, the total score now considers the previous
							//results as well as the new one.
							if (i > 0)
							{
								for (int j = 1; j <= i; j++)
								{
									round_score += *(scores + (i - j));
								
								}
								
								round_score += round_counter;
							}

							else
							{
								round_score = round_counter;
							}

							

							chooseImage(round_score);							

							
							roundText[i] = write(convert("Round ", i + 1) + convert(" : ",round_counter), 700, 70 + 70*i);


							window.clear();
							window.draw(canvas);

							for (int k = 0; k <= i; k++)
							{
								if (k != i)
								{
									roundText[k] = write(convert("Round ", k + 1) + convert(" : ", *(scores + k)), 700, 70 + 70 * k);
								}

								window.draw(roundText[k]);
								
							}//closes for k								
							
							window.display();
							round_score = 0;
						}//closes while

						round_counter = 0;

						final_score += *(scores + i);
					
					
					}//closes for i
					counting = false;
				}//closes if counting
				
				if (!counting)
				{
					window.clear();
					window.draw(canvas);

					for (int k = 0; k <= 2; k++)
					{
						roundText[k] = write(convert("Round ", k + 1) + convert(" : ", *(scores + k)), 700, 70 + 70 * k);

						window.draw(roundText[k]);
					}//closes for k	

					totalHoney = write(convert("Total Honey: ", final_score), 580, 300);
					totalHoney.setCharacterSize(22);
					window.draw(totalHoney);


					window.draw(thanks);
					blink_item();

					if (visible)
					window.draw(pressKey);

					window.display();
				}
				
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
			canvas.setTexture(&hive[0]);
		else if (final_score > 0 && final_score < 5000)
			canvas.setTexture(&hive[1]);
		else if (final_score >= 5000 && final_score < 10000)
			canvas.setTexture(&hive[2]);
		else if (final_score >= 10000 && final_score < 15000)
			canvas.setTexture(&hive[3]);
		else if (final_score >= 15000 && final_score < 20000)
			canvas.setTexture(&hive[4]);
		else if (final_score >= 20000 && final_score < 25000)
			canvas.setTexture(&hive[5]);
		else if (final_score >= 25000)
			canvas.setTexture(&hive[6]);
	}
};
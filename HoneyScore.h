/*This header file opens a new window in which the previous round scores will be displayed*/
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>


#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif

/**
*
	This class will take care of calculating the total score (Honey) based on three factors:
	1-Polen
	2-Bee's Health
	3-Number of lives

	Honey will be produced according to the followig equation:
	Honey = Polen X HP X Lives
	
	In other words, if any of the factors is equal to zero, no honey will be made.
*/

class HoneyScore:public StandartWindow
{
	

	sf::Text health_points;
	sf::Text lives_points;
	sf::Text collected_points;
	sf::Text honey_points;
	sf::Text totalPoints;
	

public:
	HoneyScore(int hp, int lives, int polen, int total_honey)
	{
		int health = 0;
		int lives_n = 0;
		int collected = 0;
		

		health = hp;
		lives_n = lives;
		collected = polen;

		

		blink.timeLimit = 2;

		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Honey Score");
		window.setFramerateLimit(60);
		

		sf::Event event;
		loadFont();


		health_points = write(convert("   HP:    ",health), WIDTH / 4, HEIGHT*0.2);
		lives_points = write(convert("   Lives: ",lives_n), WIDTH / 4, HEIGHT*0.3);
		collected_points = write(convert("   Polen: ",collected), WIDTH /4, HEIGHT*0.4);
		/*Multiply will give the aspect of a product made of hp, lives and polen collected so the user knows how 
		//The amount of honey is calculated*/
		sf::Text multiply = write("X_____________", WIDTH/4, HEIGHT*0.5);
		honey_points = write(convert("   Honey: ",total_honey), WIDTH / 4, HEIGHT *0.7);	
		
		pressKey = write("Press Enter to continue...\n", WIDTH/4, HEIGHT*0.95);

		
		//Screen Loop
		while (window.isOpen())
		{

			//Events

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				//Game goes on to the next stage if the Enter/Return key has been pressed
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Return)
					{
						window.close();
					}
				}
			}
			//Logic
			blink_item();
			//Rendering
			window.clear();
			window.draw(health_points);
			window.draw(lives_points);
			window.draw(collected_points);
			window.draw(multiply);
			window.draw(honey_points);
			window.draw(totalPoints);

			if (visible)
			{
				window.draw(pressKey);
			}
			window.display();
		}

	}

};
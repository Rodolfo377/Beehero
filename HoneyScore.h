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

class HoneyScore:public Window
{
	

	sf::Text health_points;
	sf::Text lives_points;
	sf::Text collected_points;
	sf::Text honey_points;
	
	

public:
	HoneyScore(int hp, int lives, int polen)
	{
		int health = 0;
		int lives_n = 0;
		int collected = 0;
		int total_honey = 0;

		health = hp;
		lives_n = lives;
		collected = polen;

		total_honey = hp*lives*polen;

		blink.timeLimit = 2;

		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Honey Score");
		window.setFramerateLimit(60);
		

		sf::Event event;
		loadFont();

		health_points = write(convert("HP: ",health), WIDTH / 4, HEIGHT*0.2);
		lives_points = write(convert("Lives: ",lives_n), WIDTH / 4, HEIGHT*0.4);
		collected_points = write(convert("Polen: ",collected), WIDTH /4, HEIGHT*0.6);
		honey_points = write(convert("Honey: ",total_honey), WIDTH / 4, HEIGHT *0.8);
		pressKey = write("Press any key to continue...\n", WIDTH/4, HEIGHT*0.95);

		
		//Screen Loop
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
			window.draw(health_points);
			window.draw(lives_points);
			window.draw(collected_points);
			window.draw(honey_points);

			if (visible)
			{
				window.draw(pressKey);
			}
			window.display();
		}

	}

	

	std::string convert(std::string description, int n)
	{
		/*the convertion has been adapted from http://www.cplusplus.com/articles/D9j2Nwbp/*/
		std::string Result;          // string which will contain the result

		std::ostringstream convert;   // stream used for the conversion

		convert << n;      // insert the textual representation of 'Number' in the characters in the stream

		Result = description + convert.str();

		return Result;
	}


};
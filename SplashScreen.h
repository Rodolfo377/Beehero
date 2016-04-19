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


class SplashScreen:public StandartWindow
{
private:
	sf::Texture firstImage;
	sf::RectangleShape firstWindow;


	
	

public:
	SplashScreen()
	{
	
		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Splash Screen");
		window.setFramerateLimit(60);
		sf::Event event;

		

		loadFont();
		loadImage();
		loadTitle();
		blink.timeLimit = 2;

		pressKey = write("PRESS ANY KEY TO START", WIDTH/5, HEIGHT*0.8);
		pressKey.setCharacterSize(30);

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
			//Render
			window.clear();
			window.draw(background);
			window.draw(firstWindow);
			
			if (visible == true)
			{
				window.draw(pressKey);
			}
			
			
			

			window.display();
		}
	}

private:
	void loadTitle()
	{
		if (firstImage.loadFromFile("Images/Scenario/Splash/Retro_SplashScreen.png") == 0)
		{
			std::cout << "Splash Screen not found...\n";
		}


		firstWindow.setSize(sf::Vector2f(WIDTH, HEIGHT));
		firstWindow.setPosition(0, 0);
		firstWindow.setTexture(&firstImage);
	}
};
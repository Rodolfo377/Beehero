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


class SplashScreen:public Window
{
protected:
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
		blink.timeLimit = 2;

		pressKey = write("PRESS ANY KEY TO START", WIDTH/4, HEIGHT*0.8);

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
			window.draw(firstWindow);
			
			if (visible == true)
			{
				window.draw(pressKey);
			}
			
			//Makes the Text appear and disappear every second, giving a sense o blinking
			

			window.display();
		}
	}

private:
	void loadImage()
	{
		if (firstImage.loadFromFile("Images/Scenario/Splash/splash_screen.png") == 0)
		{
			std::cout << "Splash Screen not found...\n";
		}


		firstWindow.setSize(sf::Vector2f(WIDTH, HEIGHT));
		firstWindow.setPosition(0, 0);
		firstWindow.setTexture(&firstImage);
	}
};
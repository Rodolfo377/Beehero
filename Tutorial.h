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


/*Class Tutorial is responsible for displaying the content that will introduce the player to the game,
take care of events such as pressing buttons with the cursor and making decisions based on that information.*/
class Tutorial
{
private:
	sf::Texture first_lesson;
	sf::Texture second_lesson;
	sf::RectangleShape screen;

public:
	Tutorial()
	{
		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tutorial");
		window.setFramerateLimit(60);
		loadImage();
		sf::Event event;
		

		while (window.isOpen())
		{
			

			int a = sf::Mouse::getPosition(window).x;
			int b = sf::Mouse::getPosition(window).y;
			

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					
					if (check_buttons(a, b) == 0)
						window.close();
					if (check_buttons(a, b) == 1)
						screen.setTexture(&second_lesson);
				}
			}

		

			

			window.clear();
			window.draw(screen);
			window.display();
		}

		
	}//constructor

private: 
	//loads the images from the directory that will be displayed in the window
	void loadImage()
	{
		if (first_lesson.loadFromFile("Images/Tutorial/Tutorial_1.png") == 0)
		{
			std::cout << "Could not find 'Tutorial_1.png' image...\n";
		}

		if (second_lesson.loadFromFile("Images/Tutorial/Tutorial_2.png") == 0)
		{
			std::cout << "Could not find 'Tutorial_2.png' image...\n";
		}

		screen.setTexture(&first_lesson);
		screen.setSize(sf::Vector2f(1000, 600));
		screen.setPosition(0, 0);
	}
	//checks if the cursor is over a button on the screen, and if the player clicks it will trigger a specifc task
	int check_buttons(int x, int y)
	{
		int choice = -1;

		if (x > 50 && x < 280)
		{
			if (y > 485 && y < 546)
			{
				choice = 0;
				
			}
		}
		if (x > 667 && x < 900)
		{
			if (y > 485 && y < 546)
			{
				choice = 1;
				
			}
		}


		return choice;
	}


};
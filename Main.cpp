#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include "GameComponents.h"





int main()
{

	const int WIDTH = 1000;
	const int HEIGHT = 600;
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeeHero");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	
	Elements el;
	//KeyboardEvents ke;
	
	//Variables
	int beeXVelocity = 0;
	int beeYVelocity = 0;

	//States
	
	bool play = true;
	bool gif_fly = true;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool fly_left = false;
	bool fly_right = true;
	
	//Images
	

	el.load_flowers();
	el.load_background();
	el.load_player1();

	//Sound

	//Music
	
	while (play == true)
	{
		

		/****************Events******************/
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				play = false;

			/*ke.getEvents(event, el);
			ke.runLogic();
			ke.flapWings();*/
			/*KeyBoardEvents*/
			
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				play = false;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W){
				up = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A){
				left = true; 
				fly_left = true;
				fly_right = false;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S){
				down = true; 
				el.player1.setTexture(&el.bee1_right);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D){
				fly_left = false;
				fly_right = true;
				right = true;
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W)
				up = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
				left = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
				down = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
				right = false;
		}

		/****************Logic******************/

		if (up == true) { beeYVelocity = -2; }
		if (left == true) { beeXVelocity = -2;}
		if (down == true) {beeYVelocity = 2;}
		if (right == true) { beeXVelocity = 2; }	
		if (down == false && up == false) { beeYVelocity = 0; }
		if (left == false && right == false) { beeXVelocity = 0; }
		
		el.player1.move(beeXVelocity, beeYVelocity);
		
		//Makes the bee flap its wings

		if (gif_fly == false)
		{
			if (fly_left == true)
			{
				el.player1.setTexture(&el.bee1_left);
			}
			if (fly_right == true)
			{
				el.player1.setTexture(&el.bee1_right);
			}
			gif_fly = true;
		}

		else 
		{
			if (fly_left == true)
			{
				el.player1.setTexture(&el.bee2_left);
			}
			if (fly_right == true)
			{
				el.player1.setTexture(&el.bee2_right);
			}
			
			gif_fly = false;
		}
		/****************Rendering******************/

		window.clear();
		window.draw(el.background);

		for (int j = 0; j < 3; j++)
		{
			window.draw(el.getFlower(j));
		}

		window.draw(el.player1);
		
		window.display();
	}

	window.close();
	return 0;
}
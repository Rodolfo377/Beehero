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


const int WIDTH = 1000;
const int HEIGHT = 600;
sf::Event event;

int main()
{
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeeHero");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	
	Elements el;

	el.print();
	std::cout << "x is "<<el.x << "\n";
	
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
	sf::Texture bee1_right;
	sf::Texture bee2_right;
	sf::Texture bee1_left;
	sf::Texture bee2_left;
	sf::Texture painting;

	if (bee1_right.loadFromFile("Images/bee_worker_flying_1_right.png") == false)
	{
		return 1;
	}
	if (bee2_right.loadFromFile("Images/bee_worker_flying_2_right.png") == false)
	{
		return 1;
	}

	if (bee1_left.loadFromFile("Images/bee_worker_flying_1_left.png") == false)
	{
		return 1;
	}
	if (bee2_left.loadFromFile("Images/bee_worker_flying_2_left.png") == false)
	{
		return 1;
	}

	if (painting.loadFromFile("Images/Scenario/Background/landscape under stormy sky .png") == false)
	{
		return 1;
	}
	

	//Shapes
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WIDTH, HEIGHT));
	background.setPosition(0, 0);
	background.setTexture(&painting);

	sf::RectangleShape player1;
	player1.setSize(sf::Vector2f(30, 30));
	player1.setPosition(800, 200);
	player1.setTexture(&bee1_right);
	//Sound

	//Music

	while (play == true)
	{
		

		/****************Events******************/
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				play = false;

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
				down = true; player1.setTexture(&bee1_right);
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
		
		player1.move(beeXVelocity, beeYVelocity);
		
		//Makes the bee flap its wings

		if (gif_fly == false)
		{
			if (fly_left == true)
			{
				player1.setTexture(&bee1_left);
			}
			if (fly_right == true)
			{
				player1.setTexture(&bee1_right);
			}
			gif_fly = true;
		}

		else 
		{
			if (fly_left == true)
			{
				player1.setTexture(&bee2_left);
			}
			if (fly_right == true)
			{
				player1.setTexture(&bee2_right);
			}
			
			gif_fly = false;
		}
		/****************Rendering******************/

		window.clear();
		window.draw(background);
		window.draw(player1);
		window.display();
	}

	window.close();
	return 0;
}
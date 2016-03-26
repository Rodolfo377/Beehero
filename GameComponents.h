#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>


class Elements
{
	
public:

	/*
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



	//takes two textures as arguments and alternates between them during a given period, in ms. Returns 
	//one of the two images each time it is called, based on the timing.
	sf::Texture animate(sf::Texture img1, sf::Texture img2, int milliseconds)
	{

	}*/

	int x = 5;


	void print()
	{
		std::cout << "Header function print has been called!\n";
	}
};
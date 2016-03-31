#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include "GameComponents.h"
#include "Classes.h"

/*
class Variables
{
public:
	Elements el;

	bool collecting = false;
	bool stop = false;
	bool leave = false;

	void flower_in_smooth(int, int);
	void flower_out_smooth(int, int);
	void flower_stop();
};

*/

void flower_in_smooth(const int, const int);
void flower_out_smooth(const int, const int);
void flower_stop();
void set_new_flower();

//Objects
Elements el;
Flowers rose;
Flowers violet;
Flowers orchid;
Flowers sunflower;

Flowers garden[] = { rose, violet, orchid, sunflower };
char* flower_names[] = { "rose", "violet", "orchid", "sunflower"};

Bees bumbleBee;

bool collecting = false;
bool stop = false;
bool leave = false;

const int WIDTH = 1000;
const int HEIGHT = 600;
sf::Event event;

time_t end;
time_t beginning;





//KeyboardEvents ke;

//Variables
int beeXVelocity = 0;
int beeYVelocity = 0;
int tempX = 0;
int tempY = 0;
int flower_id = 0;
int times_stop = 0;
int space_count = 0;
int flower_available;
int polen_Score = 0;
//States

bool play = true;
bool gif_fly = true;
bool up = false;
bool down = false;
bool left = false;
bool right = false;
bool fly_left = false;
bool fly_right = true;

bool space = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeeHero");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	//Variables v;
	
	//Images
	

	el.load_flowers();
	el.load_background();
	el.load_player1();

	//Sound

	//Music

	//Font
	

	set_new_flower();



	while (play == true)
	{
		el.loadTimer(time_left);
		polen_Score = bumbleBee.getPoints();
		el.loadScore(polen_Score);
		/*polen_Score = bumbleBee.getPoints();
		el.loadFont(polen_Score, el.points, 600, 10, 30);*/
		

		if (timer_check() == true)
		{
			play = false;
		}
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

			//Temporary event that will be equivalent to the time it takes to harvest a flower
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z)
			{


				stop = false;
				leave = true;
			}

			//Each time the Space Bar is pressed AND the bee has stopped upon the flower that is available
			//The bee takes a polen
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				if (stop == true)
				{
					garden[flower_available].harvest();
					bumbleBee.add_points();

					if (garden[flower_available].ripe == false)
					{
						//stop harvesting
						stop = false;
						leave = true;
					}
				}
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W)
				up = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
				left = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
				down = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
				right = false;
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				space = false;
			}
		}

		/****************Logic******************/

		if (up == true) { beeYVelocity = -3; }
		if (left == true) { beeXVelocity = -3;}
		if (down == true) {beeYVelocity = 3;}
		if (right == true) { beeXVelocity = 3; }	
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

		



		//Scanning
		for (int i = 0; i < 4; i++)
		{
			if (el.player1.getGlobalBounds().intersects(el.flowers[i].getGlobalBounds()) == true && leave == false)
			{
				if (i == flower_available)
				{
					/*******************/

					collecting = true;
					flower_id = i;
				}
			}
		}

		if (collecting == true)
		{
			 tempX = el.flowers[flower_id].getPosition().x;
			 tempY = el.flowers[flower_id].getPosition().y;

			//el.player1.move(tempX, tempY);
			
			 if (stop == false && leave == false)
			 {
				 
				 //Smooth placement onto the flower
				 
				 flower_in_smooth(tempX, tempY);
			 }
			 //Holds the bee on the flower while it collects pollen
			 if (stop == true)
			 {
				 flower_stop();
			 }

			 //Smooth transition out of the flower
			 if (stop == false && leave == true)
			 {
				 flower_out_smooth(tempX, tempY);
			 }
			 
		}
		/****************Rendering******************/

		window.clear();
		window.draw(el.background);

		for (int j = 0; j < 4; j++)
		{
			window.draw(el.getFlower(j));
		}

		window.draw(el.player1);
		window.draw(el.timer);
		window.draw(el.points);
		window.display();

		//std::cout << "\ncollecting: " << collecting << " tempX = " << tempX << " tempY = " << tempY;
	}

	window.close();
	return 0;
}

void flower_in_smooth(const int tempX, const int tempY)
{
	
	if (el.player1.getPosition().x < tempX + 20)
		el.player1.move(1, 0);
	if (el.player1.getPosition().y < tempY)
		el.player1.move(0, 1);
	if (el.player1.getPosition().x > tempX + 20)
		el.player1.move(-1, 0);
	if (el.player1.getPosition().y > tempY)
		el.player1.move(0, -1);
	if (el.player1.getPosition().x == tempX + 20 && el.player1.getPosition().y == tempY)
		stop = true; 
}

void flower_stop()
{
	times_stop += 1;
	fly_right = true;
	el.player1.setPosition(tempX + 20, tempY);
	
	/*
	if (times_stop == 1)
	{
		beginning = time(NULL);

	}

	end = time(NULL);

	//If the bee has spent more than 5 seconds harvesting the flower, it leaves the flower.
	if (difftime(end, beginning) >= 5)
	{
		times_stop = 0;
		stop = false;
		leave = true;
	}*/

}

void flower_out_smooth(const int tempX, const int tempY)
{
	if (el.player1.getPosition().y >= tempY - 40)
	{
		el.player1.move(0, -3);
		std::cout << " leaving...\n";
	}
	else
	{
		std::cout << " left!\n";
		leave = false;
		collecting = false;
		/*
		resets flower_index to a non-existing array index,
		and it will only be valid once it is redifined on
		the next Scanning that finds a collision with one
		of the flowers and the bee.*/
		flower_id = 1000;
		set_new_flower();
	}
}

void set_new_flower()
{
	flower_available = random_n_generator(0, 4);
	garden[flower_available].setValues(6, true);
	std::cout << "polen: " << garden[flower_available].polen << std::endl;
	std::cout << flower_names[flower_available] << std::endl;
	el.setEmptyFlowers(flower_available);
}

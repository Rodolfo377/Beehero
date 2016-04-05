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

/*The source code is adapted from a Udemy Course called 'Learn c++ game development' https://www.udemy.com/learn-c-game-development/
in which the basic functionality of the SFML library is explored. However, this game has its own mechanics and art.*/

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

class StartGame
{
	//function protoypes
	/*void flower_in_smooth(const int, const int);
	void flower_out_smooth(const int, const int);
	void flower_stop();
	void set_new_flower();
	void create_drop();
	void move_drop();
	void take_damage();
	bool detect_collision_water();
	void blink_bee();
	*/

	//Objects
	Elements el;
	Flowers rose;
	Flowers violet;
	Flowers orchid;
	Flowers sunflower;
	Flowers garden[4];
	Methods game;
	Methods plus_one;
	Methods r;
	////object that will be responsible for calling the timer_check method in order to slow the bee down when it gets hurt
	Methods h;
	//object that will be responsible for calling the timer_check method in order to show the image of the bee on the screen
	//Will be useful when the bee is hit by a water drop
	Methods s;

	sf::SoundBuffer collectBuffer;
	sf::SoundBuffer waterBuffer;
	sf::Sound collect;
	sf::Sound hit;

	const int WIDTH = 1000;
	const int HEIGHT = 600;

	

	Bees bumbleBee;

	bool collecting = false;
	bool stop = false;
	bool leave = false;




	
	sf::Event event;

	time_t end;
	time_t beginning;



	///////Variables
	int beeXVelocity = 0;
	int beeYVelocity = 0;
	//tempX holds the temporary x coordinate of the flower that is available to be harvested
	int tempX = 0;
	//tempX holds the temporary y coordinate of the flower that is available to be harvested
	int tempY = 0;
	//index of the flower that is available
	int flower_id = 0;
	int times_stop = 0;
	int space_count = 0;
	int flower_available;
	int polen_Score = 0;
	int fly_counter = 0;
	int health_points = 0;
	//collision_counter variable determines how many times the function take_damage has been called, so it wont unnecessarily repeat its comands
	int collision_counter = 0;
	//blink variable determines how many times the bee has blinked - used in blink_bee() function
	int blink = 0;
	int speed;

	//States

	bool play = true;
	bool gif_fly = true;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool fly_left = false;
	bool fly_right = true;
	bool harvesting = false;
	bool space = false;
	bool show_bee = true;
	//hurt tells if the bee was struck by a water drop
	bool hurt = false;


	//vector that holds the water drops sprites that, when combined, will be the rain
	std::vector<sf::Sprite> rain;

public:
	StartGame()
	{
		
		//Variables v;

		//Images


		el.load_flowers();
		el.load_background();
		el.load_player1();
		el.loadRain();

		//Sound
		

		if (collectBuffer.loadFromFile("Sound/polen_pickup.wav") == 0)
		{
			std::cout << "'polen_pickup.wav' not found...\n";
		}
		if (waterBuffer.loadFromFile("Sound/water_hit.wav") == 0)
		{
			std::cout << "'water_hit.wav' not found...\n";
		}

		collect.setBuffer(collectBuffer);
		hit.setBuffer(waterBuffer);
		//Music

		//Font

		 speed = 3;

		set_new_flower();

		game.timeLimit = 90;
		plus_one.timeLimit = 1;
		el.loadScoreSprite(flower_available);

		rain.push_back(el.rainSprite);
		r.timeLimit = 2;

		//garden[4] = { rose, violet, orchid, sunflower };
		garden[0] = rose;
		garden[1] = violet;
		garden[2] = orchid;
		garden[3] = sunflower;
	
		char* flower_names[] = { "rose", "violet", "orchid", "sunflower" };

		
	}

	bool gameLoop()
	{
		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeeHero");

		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(false);
			while (play == true)
			{


				el.loadTimer(game.time_left);
				polen_Score = bumbleBee.getPoints();
				health_points = bumbleBee.get_hp();
				el.loadScore(polen_Score);
				el.load_hp(health_points);
				/*polen_Score = bumbleBee.getPoints();
				el.loadFont(polen_Score, el.points, 600, 10, 30);*/

				//If the game time's up or the bee has taken 10 hp of damage, game is over
				if (game.timer_check() <= 0 || bumbleBee.get_hp() == 0)
				{
					play = false;
				}

				//make rain again
				if (game.timer_check() % 15 == 0 && game.timer_check() < 70)
				{
					for (int i = 0; i < rain.size(); i++)
					{
						rain[i].setPosition(70 + (i)* 75, 0);
					}
				}

				//Every 2 seconds loads a new rain drop sprite

				if (rain.size() < 10)
				{
					create_drop();
				}
				move_drop();




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

						std::cout << "Z!\n";
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
							harvesting = true;
							el.loadScoreSprite(flower_available);
							collect.play();

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

				if (up == true) { beeYVelocity = -speed; }
				if (left == true) { beeXVelocity = -speed; }
				if (down == true) { beeYVelocity = speed; }
				if (right == true) { beeXVelocity = speed; }
				if (down == false && up == false) { beeYVelocity = 0; }
				if (left == false && right == false) { beeXVelocity = 0; }

				//If a water drop struck the bee, it gets hurt and therefore it moves slowly 

				if (hurt == true)
				{

					blink_bee();
					//sets the timer to 2 seconds, that is how long the bee will move slower and blink
					h.timeLimit = 2;
					speed = 1;

					if (h.timer_check() <= 0){ hurt = false; h.reset_timer(); show_bee = true; }
				}

				if (hurt == false)
				{
					speed = 3;
				}
				el.player1.move(beeXVelocity, beeYVelocity);

				if (harvesting == true)
				{
					//moves the '+1' sprite upwards
					el.sprite_score.move(0, -1);
					fly_counter++;

					//when the '+1' sprite has moved 50 pixels
					if (fly_counter == 50)
					{

						harvesting = false;
						fly_counter = 0;
					}

				}
				if (harvesting == false)
				{
					el.loadScoreSprite(flower_available);
				}


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

				//Checks if a water drop hit a bee
				if (detect_collision_water() == true)
				{
					take_damage();
					if (collision_counter == 1)
						hit.play();

				}
				if (detect_collision_water() == false)
				{
					collision_counter = 0;
				}



				//Scanning
				for (int i = 0; i < 4; i++)
				{	//if the bee is inside the flower space, the index of the flower 
					//is saved and the boolean variable collecting is set to true, which triggers the methods that will:
					//1) guide the bee towards the center of the flower 
					//2)  hold it there so the player can start harvesting the flower
					//3) once the player is done harvesting - polen runs out- the bee will be lifted just above the flower and set free
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

				//draws all the 4 flowers on the screen
				for (int j = 0; j < 4; j++)
				{
					window.draw(el.getFlower(j));
				}
				//std::cout << "harvesting: " << harvesting << "\n";
				if (show_bee == true)
				{
					window.draw(el.player1);
				}
				window.draw(el.timer);
				window.draw(el.points);
				window.draw(el.health);

				for (int i = 0; i < rain.size(); i++)
				{
					window.draw(rain[i]);

				}

				if (harvesting == true)
				{
					window.draw(el.sprite_score);
				}


				window.display();

			}

			window.close();
			//End game
			return play;
		
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


	}

	void flower_out_smooth(const int tempX, const int tempY)
	{
		if (el.player1.getPosition().y >= tempY - 40)
		{
			el.player1.move(0, -3);
			//std::cout << " leaving...\n";
		}
		else
		{
			//std::cout << " left!\n";
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
		flower_available = game.random_n_generator(0, 4);
		garden[flower_available].setValues(6, true);
		/*std::cout << "polen: " << garden[flower_available].polen << std::endl;
		std::cout << flower_names[flower_available] << std::endl;*/
		el.setEmptyFlowers(flower_available);
	}

	void create_drop()
	{
		//small pause after the drop is created then moved
		//works until the second to last drop
		if (r.timer_check() <= 0)
		{

			rain.push_back(el.rainSprite);
			r.reset_timer();

		}
		//places the last created drop at a specific place

		rain[rain.size() - 1].setPosition(70 + (rain.size()) * 75, 0);


	}

	void move_drop()
	{

		for (int i = 0; i < rain.size(); i++)
		{
			//if it is the last drop, add a 2 second pause
			if (i >= 9)
			{
				if (r.timer_check() <= 0)
				{
					rain[i].move(0, 2);
				}
			}
			else
			{
				rain[i].move(0, 2);
			}
		}
	}

	bool detect_collision_water()
	{
		bool wet = false;
		for (int i = 0; i < rain.size(); i++)
		{
			if (el.player1.getGlobalBounds().intersects(rain[i].getGlobalBounds()) == true)
			{
				wet = true;

			}

		}
		return wet;
	}

	//If the bee gets hit by a water drop, its polen score gets reduced to 60% 
	//of the previous value, and its health drops by half
	void take_damage()
	{
		collision_counter++;

		if (collision_counter == 1)
		{
			int p = bumbleBee.getPoints();
			bumbleBee.setPoints(p*0.6);

			int q = bumbleBee.get_hp();
			bumbleBee.set_hp((int)q*0.5);
			hurt = true;
		}
	}

	void blink_bee()
	{
		blink++;

		if (blink % 3 == 0)
		{
			show_bee = true;
		}
		else{ show_bee = false; }
	}

};
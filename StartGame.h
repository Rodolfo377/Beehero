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
#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif



/*The source code is adapted from a Udemy Course called 'Learn c++ game development' https://www.udemy.com/learn-c-game-development/
in which the basic functionality of the SFML library is explored. However, this game has its own mechanics and art.*/



class StartGame
{
	

	//Objects

	Elements el;
	Flowers rose;
	Flowers violet;
	Flowers orchid;
	Flowers sunflower;
	Flowers garden[4];
	Methods game;
	//object that
	Methods steady_rain;
	//r object that will serve to set the 2 seconds timer each rain drop has between each other at the begginning
	Methods r;
	////object that will be responsible for calling the timer_check method in order to slow the bee down when it gets hurt
	Methods h;
	//object that will be responsible for calling the timer_check method in order to show the image of the bee on the screen
	//Will be useful when the bee is hit by a water drop
	Methods s;

	sf::SoundBuffer collectBuffer;
	sf::SoundBuffer waterBuffer;
	sf::SoundBuffer hpBoostBuffer;
	sf::SoundBuffer timeBoostBuffer;
	sf::SoundBuffer LifeUpBuffer;

	sf::Sound collect;
	sf::Sound hit;
	sf::Sound hp_boost;
	sf::Sound time_boost;
	sf::Sound lifeUp;

	Bees bumbleBee;
	sf::Event event;

	

	//vector that holds the water drops sprites that, when combined, will be the rain
	std::vector<sf::Sprite> rain;

	//array that holds the position index of the rain drop (from left to right) and the item index (see method place_item())
	//and it does so for 3 different items: 3x2 = 6 places.
	int special_item[6];


	//constants that will be used through the code

	const int drops_number = 14;
	

public:
	StartGame()
	{

		

		//Images


		el.load_flowers();
		el.load_background();
		el.load_player1();
		//sets the rain drops to their default image
		el.loadRain(0);
		


		//Sound


		if (collectBuffer.loadFromFile("Sound/polen_pickup.wav") == 0)
		{
			std::cout << "'polen_pickup.wav' not found...\n";
		}
		if (waterBuffer.loadFromFile("Sound/water_hit.wav") == 0)
		{
			std::cout << "'water_hit.wav' not found...\n";
		}
		if (hpBoostBuffer.loadFromFile("Sound/hp_boost.wav") == 0)
		{
			std::cout << "'hp_boost.wav' not found...\n";
		}
		if (timeBoostBuffer.loadFromFile("Sound/time_boost.wav") == 0)
		{
			std::cout << "'time_boost.wav' not found...\n";
		}
		if (LifeUpBuffer.loadFromFile("Sound/life_up.wav") == 0)
		{
			std::cout << "'life_up.wav' not found...\n";
		}

		collect.setBuffer(collectBuffer);
		hit.setBuffer(waterBuffer);
		hp_boost.setBuffer(hpBoostBuffer);
		time_boost.setBuffer(timeBoostBuffer);
		lifeUp.setBuffer(LifeUpBuffer);
		//Music

		

		

		game.timeLimit = 90;

		

		rain.push_back(el.rainSprite);
		r.timeLimit = 2;

		
		//garden[4] = { rose, violet, orchid, sunflower };
		garden[0] = rose;
		garden[1] = violet;
		garden[2] = orchid;
		garden[3] = sunflower;

		char* flower_names[] = { "rose", "violet", "orchid", "sunflower" };
		

	}

	public: bool gameLoop(int stage)
	{
	 
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
		//item_picked will indicate if the player has collected an item, and then it will play the proper sound effect to it
		bool item_picked = false;
		/*placed tells us if the random_place method has been called at least once, which will trigger specific collision
		tests for the rain drop and the player, because from the moment there are items inside the rain drops,
		it will have different effects on the player rather than just damage its health or making the bee lose
		polen.
		*/
		bool placed = false;

		//hurt tells if the bee was struck by a water drop
		bool hurt = false;
		bool invisible_drop = false;
		bool first_loop = true;

		bool collecting = false;
		bool stop = false;
		bool leave = false;


		//Basic window setup
		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BeeHero");
		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(false);


		//speed of the bee, in pixels per iteration
		int speed = 2;

		/*drop_strike holds the value related to the water drop that hit the player at a cetain moment
		It is initialized as an invalid index, if compared to the vector of rainSprites that will be created.
		There will be no more than two dozens of them at a time in the screen.*/
		int drop_strike = 0;


		int beeXVelocity = 0;
		int beeYVelocity = 0;
		//tempX holds the temporary x coordinate of the flower that is available to be harvested
		int tempX = 0;
		//tempX holds the temporary y coordinate of the flower that is available to be harvested
		int tempY = 0;
		//index of the flower that is available (from 0 to 3)
		int flower_id = 0;
		int times_stop = 0;
		int space_count = 0;
		
		int polen_Score = 0;
		int fly_counter = 0;
		int health_points = 0;
		//collision_counter variable determines how many times the function take_damage has been called, so it wont unnecessarily repeat its comands
		int collision_counter = 0;
		//blink variable determines how many times the bee has blinked - used in blink_bee() function
		int blink = 0;

		//array that holds the position index of the rain drop (from left to right) and the item index (see method place_item())
		//and it does so for 3 different items: 3x2 = 6 places.
		int water_item[6];
		
		int flower_available = 0;
		set_new_flower(flower_available);
		el.loadScoreSprite(flower_available);

		//The more advanced the stage, the more frequently rain is going to fall
		steady_rain.timeLimit = 20 / stage;
		
		while (play == true)
		{


			el.loadTimer(game.time_left);
			polen_Score = bumbleBee.getPoints();
			health_points = bumbleBee.get_hp();
			el.loadScore(polen_Score);
			el.load_hp(health_points);
			el.load_lives(bumbleBee.getLives());
			/*polen_Score = bumbleBee.getPoints();
			el.loadFont(polen_Score, el.points, 600, 10, 30);*/

			//If the game time's up or the bee has taken 10 hp of damage, game is over
			if (game.timer_check() <= 0 || bumbleBee.get_hp() == 0)
			{
				play = false;
			}

			//makes it rain again every 15, 10 or 5 seconds seconds, after 20 seconds have passed
			if (game.timer_check() < 65 && steady_rain.timer_check() <= 0)
			{
				
				drop_strike = 0;
				invisible_drop = false;
				steady_rain.reset_timer();
				for (int i = 1; i < (int)rain.size(); i++)
				{
					rain[i-1].setPosition( (int)i* 75 - 10, 0);
					/*sets all the sprites to the default image- so in case the player
					reaches 100 points but loses it, the item wont be there again, but
					the drops will all be reset to be empty once more*/
					rain[i-1].setTexture(el.water_drop);
				}
				//places a special item inside a rain drop
				if (bumbleBee.getPoints() > 30)
				{
					int *p;
					p = place_item();

					//copies the values from the array yielded by the method place_item() into water_item
					for (int k = 0; k <= 5; k++)
					{
						water_item[k] = p[k];
						/*std::cout << "\nwater_item[" << k << "] = " << water_item[k] << "\n";
						std::cout << "p[" << k << "] = " << p[k] << "\n";*/

					}
					placed = true;
					//make a small pause before move the rain drops downwards
					r.reset_timer();
				}
			}

			//Every 2 seconds loads a new rain drop sprite

			if ((int)rain.size() < drops_number)
			{
				create_drop();
			}

			move_drop(placed, speed);






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
						bumbleBee.add_points(1*stage);
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

				blink_bee(show_bee, blink);
				//sets the timer to 2 seconds, that is how long the bee will move slower and blink
				h.timeLimit = 2;
				//slows the bee and the rain speed, giving a sense of slow-motion
				speed = 1;

				if (h.timer_check() <= 0){ hurt = false; h.reset_timer(); show_bee = true; }
			}

			if (hurt == false)
			{
				speed = 2*stage;
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
			if (detect_collision_water(drop_strike) == true)
			{
				invisible_drop = true;
				/*assesses if the water drop that has collided with the player contains an item in it
				or not, and decides what is the effect the water dorp has on the player depending on
				the circumstances*/
				take_damage(placed, hurt, item_picked, collision_counter, drop_strike, water_item);
				/*if the collision has only been detected once and the water drop does not contain an item,
				play a sound effect for being hit*/
				if (collision_counter == 1 && item_picked == false)
					hit.play();

				//resets the variable so the hit sound can be played again
				item_picked = false;
			}
			if (detect_collision_water(drop_strike) == false)
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
				tempX = (int)el.flowers[flower_id].getPosition().x;
				tempY = (int)el.flowers[flower_id].getPosition().y;

				//el.player1.move(tempX, tempY);

				if (stop == false && leave == false)
				{

					//Smooth placement onto the flower

					flower_in_smooth(tempX, tempY, stop);
				}
				//Holds the bee on the flower while it collects pollen
				if (stop == true)
				{
					flower_stop(fly_right, times_stop, tempX, tempY);
				}

				//Smooth transition out of the flower
				if (stop == false && leave == true)
				{
					flower_out_smooth(tempX, tempY, flower_id, flower_available, leave, collecting, speed);
				}

			}

			//Checks if bee is inside the window boundaries
			//x-axis, invert the current x velocity of the bee
			if (el.player1.getPosition().x < 0 || el.player1.getPosition().x > WIDTH - 30)
				el.player1.move(-beeXVelocity, 0);
			//y-axis
			if (el.player1.getPosition().y < 0 || el.player1.getPosition().y > HEIGHT - 30)
				el.player1.move(0, -beeYVelocity);

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
			window.draw(el.lives);

			for (int i = 0; i < (int)rain.size(); i++)
			{
				/*If a water drop collided with the bee, it will disappear-wont be drawn anymore*/
				if (invisible_drop == true)
				{
					if (i != drop_strike)
					{
						window.draw(rain[i]);
					}
				}
				else{ window.draw(rain[i]); }


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

	/*controls the access to all of the following functions:
	flower_in_smooth()
	flower_stop()
	flower_out_smooth()
	set_new_flower()
	create_drop()
	move_drop()
	detect_collision_water()
	take_damage()
	blink_bee()
	place_item()
	*/
	private:

	void flower_in_smooth(const int tempX, const int tempY, bool &stop)
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

	void flower_stop(bool &fly_right, int &times_stop, const int tempX, const int tempY)
	{
		times_stop += 1;
		fly_right = true;
		el.player1.setPosition((int)tempX + 20, (int)tempY);


	}

	void flower_out_smooth(const int tempX, const int tempY, int &flower_id,  int &flower_available, bool &leave, bool &collecting, const int speed)
	{
		if (el.player1.getPosition().y >= tempY - 40)
		{
			el.player1.move(0, (int)-speed);
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
			set_new_flower(flower_available);
		}
	}

	void set_new_flower(int &flower_available)
	{
		flower_available = game.random_n_generator(0, 4);
		garden[flower_available].setValues(7, true);
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

		rain[rain.size() - 1].setPosition( (float)((rain.size()) * 75)  - 10, 0);


	}

	void move_drop(const bool placed, const int speed)
	{
		if (placed == false)
		{
			for (int i = 0; i < (int)rain.size(); i++)
			{
				//if it is the last drop, add a 2 second pause

				if (i >= (int)rain.size()-1)
				{
					if (r.timer_check() <= 0)
					{
						rain[i].move(0, (int)speed);
					}//if
				}//if

				else
				{
					rain[i].move(0, (int)speed);
				}//else
			}//for
		}//if(placed == false)
		if (placed == true && r.timer_check() <= 0)
		{

			for (int j = 0; j < (int)rain.size(); j++)
			{
				rain[j].move(0, (int)speed);
			}


		}//if (placed == true)



	}//move_drop()

	bool detect_collision_water(int &drop_strike)
	{
		bool wet = false;
		for (int i = 0; i < (int)rain.size(); i++)
		{
			if (el.player1.getGlobalBounds().intersects(rain[i].getGlobalBounds()) == true)
			{
				wet = true;
				drop_strike = i;
			}

		}
		return wet;
	}

	//If the bee gets hit by a water drop, its polen score gets reduced to 60% 
	//of the previous value, and its health drops by half
	//However, if the bee catches a drop that has an item in it, the proper effects are taking place
	void take_damage(const bool placed, bool &hurt, bool &item_picked, int &collision_counter, const int drop_strike, const int *p)
	{
		collision_counter++;

		if (collision_counter == 1)
		{
			if (placed == false)
			{


				int p = bumbleBee.getPoints();
				bumbleBee.setPoints((int)p*0.6);

				int q = bumbleBee.get_hp();
				bumbleBee.set_hp((int)q*0.5);
				hurt = true;

			}
			else//placed == true
			{

				bool yes_it_hurt = false;
				//tests if the bee was struck by a drop containing an item
				for (int i = 0; i < 6; i += 2)
				{
					if (drop_strike == p[i])
					{
						item_picked = true;
						//if so, checks what item is it and then decides what the response is going to be
						switch (p[i + 1])
						{
						case 1://death item
							//wipes out the bumblebee's life
							bumbleBee.alter_lives(-1);
							//resets the hp to maximum
							bumbleBee.set_hp(10);
							//if it was the bee's last life, it perishes
							if (bumbleBee.getLives() == 0)
								bumbleBee.set_hp(0);
							//std::cout << "Died! \n";
							break;
						case 2://heart item
							//Adds 5 to the bumblebee's hp
							if (bumbleBee.get_hp() + 5 <= 10)
							{
								bumbleBee.add_hp(5);
								hp_boost.play();
							}
							/*However, if the bee is left with over 10 hp it will be automatically set to 10 again and the player will
							//be awarded with an extra life instead*/
							else if (bumbleBee.get_hp()+5 > 10)
							{
								bumbleBee.set_hp(10);
								bumbleBee.alter_lives(1);
								//load triumph sound
								lifeUp.play();
							}
							//plays a specific sound effect 
							
							break;
						case 3://time item
							//gives the player 15 more seconds of play
							game.timeLimit += 15;
							//plays a specific sound effect 
							time_boost.play();
							break;
						default:
							break;
						}//closes switch
					}//closes drop_strike if

					//if there was a collision, and no item has already been taken, it must be an empty drop, so it will hurt the bee 
					if (drop_strike != p[i] && item_picked == false && yes_it_hurt == false)
					{
						yes_it_hurt = true;
						int p = bumbleBee.getPoints();
						bumbleBee.setPoints((int)p*0.6);

						int q = bumbleBee.get_hp();
						bumbleBee.set_hp((int)q*0.5);
						hurt = true;

					}
				}
			}//closes else (placed == true)
		}
	}

	void blink_bee( bool &show_bee, int &blink)
	{
		
		blink++;

		if (blink % 3 == 0)
		{
			show_bee = true;
		}
		else{ show_bee = false; }
	}

	/*after the player has scored enough points, random items may be found inside the one of the rain drops
	//this function will place a random item inside a water drop from the 4th to the 10th rain array elements, from left to right
	//Also, two pre-defined items (purple death skull) will be located at each side of the random item.
	
	The function starts by placing the random item (time boost, health boost, or death skull), identified by the parameter 'itemcode'*/
	int * place_item()
	{
		int itemcode = 0;
		int item_id = 0, drop_id = 0;
		

		while (itemcode <= 4)
		{
			//if the parameter is 0, a random item will be placed at a random place
			if (itemcode == 0)
			{
				//sets the rain drop in which the item is going to be in  random fashion
				//designed to be located as centre as possible (i.e., close to the flowers and the player)
				//int limit = drops_number - 4;
				drop_id = game.random_n_generator(3, 6);
				
		
				//sets the item that is going to be displayed inside the chosen rain drop
				item_id = game.random_n_generator(1, 3);
			}


			//places at least one death item besides another item
			//itemcode values 1 and 2 are used so in different iteractions it can place the
			//deadly items besides a random item, using the variable item_id.
			if (itemcode == 2 || itemcode == 4)
			{
				int temp_id = drop_id;
				item_id = 1;

				if (itemcode == 2)
				{
					if (drop_id < drops_number-1)
						drop_id = temp_id + 1;
				}
				if (itemcode == 4)
				{
					if (drop_id > 1)
						drop_id = temp_id - 2;
				}

			}

			switch (item_id)
			{

			case 1:
				rain[drop_id].setTexture(el.water_death);
				break;
			case 2:
				rain[drop_id].setTexture(el.water_heart);
				break;
			case 3:
				rain[drop_id].setTexture(el.water_time);
				break;
			default:
				break;
			}
			special_item[itemcode] = drop_id;
			special_item[itemcode + 1] = item_id;
			itemcode += 2;
		}
		return special_item;
	}

	public:

	int getBeeLives()
	{
		return bumbleBee.getLives();
	}
	int getBeePolen()
	{
		return bumbleBee.getPoints();
	}
	int getBeeHP()
	{
		return bumbleBee.get_hp();
	}
};
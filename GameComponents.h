#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <vector>


class Elements
{
	
private:

	sf::Texture flower_tex[4];
	sf::Texture flower_empty[4];
	sf::Texture painting;
	sf::Texture mission_background;
	sf::Texture plus_one;
	sf::Texture fall;
	sf::Texture spring;
	sf::Texture summer;
	sf::Texture summer_special;
	sf::Texture special_sprites[7];
	

	int sprite_index = -1;
	int tempXflower = 0;
	int tempYflower = 0;

	


public:
	sf::Texture bee1_right;
	sf::Texture bee2_right;
	sf::Texture bee1_left;
	sf::Texture bee2_left;
	sf::Texture water_heart;
	sf::Texture water_time;
	sf::Texture water_death;
	sf::Texture water_drop;

	sf::RectangleShape background;
	sf::RectangleShape flowers[4];
	sf::RectangleShape player1;
	sf::Sprite bonus_rectangle;

	sf::Sprite rainSprite;
	

	//Font
	sf::Font font;
	sf::Text timer;
	sf::Text points;
	sf::Text health;
	sf::Text lives;

	sf::Sprite sprite_score;
	

	//Sound
	
	

public:

	Elements()
	{
		if (!flower_tex[0].loadFromFile("Images/Scenario/flowers/rose_full.png"))
		{
			std::cout << "Could not find 'rose_full.png' image...\n";
		}

		if (!flower_tex[1].loadFromFile("Images/Scenario/flowers/violet_full.png"))
		{
			std::cout << "Could not find 'violet_full.png' image...\n";
		}

		if (!flower_tex[2].loadFromFile("Images/Scenario/flowers/orchid_full.png"))
		{
			std::cout << "Could not find 'sunflower_full.png' image...\n";
		}

		if (!flower_tex[3].loadFromFile("Images/Scenario/flowers/sunflower_full.png"))
		{
			std::cout << "Could not find 'orchid_full.png' image...\n";
		}

		//Empty

		if (!flower_empty[0].loadFromFile("Images/Scenario/flowers/rose_empty.png"))
		{
			std::cout << "Could not find 'rose_full.png' image...\n";
		}

		if (!flower_empty[1].loadFromFile("Images/Scenario/flowers/violet_empty.png"))
		{
			std::cout << "Could not find 'violet_full.png' image...\n";
		}

		if (!flower_empty[2].loadFromFile("Images/Scenario/flowers/orchid_empty.png"))
		{
			std::cout << "Could not find 'orchid_full.png' image...\n";
		}

		if (!flower_empty[3].loadFromFile("Images/Scenario/flowers/sunflower_empty.png"))
		{
			
			std::cout << "Could not find 'sunflower_full.png' image...\n";
		}

		//Images of bee flying

		if (bee1_right.loadFromFile("Images/bee_worker_flying_1_right.png") == false)
		{
			std::cout << "Could not find 'bee_worker_flying_1_right.png' image...\n";
		}
		if (bee2_right.loadFromFile("Images/bee_worker_flying_2_right.png") == false)
		{
			std::cout << "Could not find 'bee_worker_flying_2_right.png' image...\n";
		}

		if (bee1_left.loadFromFile("Images/bee_worker_flying_1_left.png") == false)
		{
			std::cout << "Could not find 'bee_worker_flying_1_left.png' image...\n";
		}
		if (bee2_left.loadFromFile("Images/bee_worker_flying_2_left.png") == false)
		{
			std::cout << "Could not find 'bee_worker_flying_2_left.png' image...\n";
		}

		if (painting.loadFromFile("Images/Scenario/Background/landscape_under_stormy_sky.png") == false)
		{
			std::cout << "Could not find 'landscape_under_stormy_sky.png' image...\n";
		}

		if (mission_background.loadFromFile("Images/Scenario/background/MahGrassField.png") == false)
		{
			std::cout << "Could not find 'MahGrassField.png' image...\n";
		}

		//Font
		if (font.loadFromFile("Fonts/PressStart2P.ttf") == 0)
		{
			std::cout << "Could not find 'PressStart2P.ttf font...\n";
		}

		//Sprites
		if (plus_one.loadFromFile("Images/Sprites/Plus_one.png") == 0)
		{
			std::cout << "Could not find 'Plus_one.png'\n";
		}

		if (water_drop.loadFromFile("Images/Scenario/Obstacles/water_drop.png") == 0)
		{
			std::cout << "Could not find 'water_drop.png'...\n";
		}

		if (water_heart.loadFromFile("Images/Scenario/Obstacles/water_heart.png") == 0)
		{
			std::cout << "Could not find 'water_heart.png'...\n";
		}

		if (water_time.loadFromFile("Images/Scenario/Obstacles/water_time.png") == 0)
		{
			std::cout << "Could not find 'water_time.png'...\n";
		}

		if (water_death.loadFromFile("Images/Scenario/Obstacles/water_death.png") == 0)
		{
			std::cout << "Could not find 'water_death.png'...\n";
		}

		//Background images of each level
		if (spring.loadFromFile("Images/Scenario/background/spring_background.png") == 0)
		{
			std::cout << "Could not find 'spring_background.png'...\n";
		}

		if (summer.loadFromFile("Images/Scenario/background/summer_background.png") == 0)
		{
			std::cout << "Could not find 'summer_background.png'...\n";
		}

		if (summer_special.loadFromFile("Images/Scenario/background/summer_background_2.png") == 0)
		{
			std::cout << "Could not find 'summer_background_2.png'...\n";
		}

		if (fall.loadFromFile("Images/Scenario/background/fall_background.png") == 0)
		{
			std::cout << "Could not find 'fall_background.png'...\n";
		}

		//Bonus items sprites
		if (special_sprites[0].loadFromFile("Images/Sprites/plus_five.png") == 0)
		{
			std::cout << "Could not find 'plus_five.png'...\n";
		}

		if (special_sprites[1].loadFromFile("Images/Sprites/1up.png") == 0)
		{
			std::cout << "Could not find '1up.png'...\n";
		}

		if (special_sprites[2].loadFromFile("Images/Sprites/plus_twenty.png") == 0)
		{
			std::cout << "Could not find 'plus_twenty.png'...\n";
		}

		if (special_sprites[3].loadFromFile("Images/Sprites/10s.png") == 0)
		{
			std::cout << "Could not find '10s.png'...\n";
		}

		if (special_sprites[4].loadFromFile("Images/Sprites/bee_ghost_left.png") == 0)
		{
			std::cout << "Could not find 'bee_ghost_left.png'...\n";
		}

		if (special_sprites[5].loadFromFile("Images/Sprites/bee_ghost_right.png") == 0)
		{
			std::cout << "Could not find 'bee_ghost_right.png'...\n";
		}

		if (special_sprites[6].loadFromFile("Images/Sprites/plus_fifty.png") == 0)
		{
			std::cout << "Could not find 'plus_fifty.png'...\n";
		}
		
	}

	//This loads the image on the window, placing each of the RectangleShape objects in a certain place
	void load_flowers()
	{
			//0
			flowers[0].setSize(sf::Vector2f(100, 100));
			flowers[0].setPosition(400, 120);
			flowers[0].setTexture(&flower_tex[0]);

			//1
			flowers[1].setSize(sf::Vector2f(100, 100));
			flowers[1].setPosition(625, 300);
			flowers[1].setTexture(&flower_tex[1]);

			//2
			flowers[2].setSize(sf::Vector2f(100, 100));
			flowers[2].setPosition(400, 480);
			flowers[2].setTexture(&flower_tex[2]);

			//3
			flowers[3].setSize(sf::Vector2f(100, 100));
			flowers[3].setPosition(175, 300);
			flowers[3].setTexture(&flower_tex[3]);
		
	}

	sf::RectangleShape getFlower(int index)
	{
		return flowers[index];
	}

	void load_background(int level)
	{
		background.setSize(sf::Vector2f((float)1000, (float)600));
		background.setPosition(0, 0);
		

		if (level == 1)
		{
			background.setTexture(&spring);
		}

		if (level == 2)
		{
			background.setTexture(&summer);
		}

		if (level == 3)
		{
			background.setTexture(&fall);
		}
	}

	sf::RectangleShape getBackground()
	{
		return background;
	}

	void load_player1()
	{
		player1.setSize(sf::Vector2f(30, 30));
		player1.setPosition(430, 300);
		player1.setTexture(&bee1_right);
	}
	sf::RectangleShape getPlayer1()
	{
		return player1;
	}

	/*loadTimer() takes an integer as an argument and converts the number to a string, later to be transformed into a Text object
	//To be printed on the screen*/
	void loadTimer(int sec)
	{
		std::string seconds;

		std::ostringstream convert;
		convert << sec;
		seconds = convert.str();
		
		
		timer.setFont(font);
		timer.setCharacterSize(20);
		timer.setString("Time:"+seconds+"s");

		timer.setPosition(0, 10);
	}
	/*loaadScore() takes an integer as an argument and converts the number to a string, later to be transformed into a Text object
	//To be printed on the screen*/
	void loadScore(int n)
	{
		std::string score;
		std::ostringstream convert;

		convert << n;
		score = convert.str();


		points.setFont(font);
		points.setCharacterSize(20);
		points.setString(" Score:"+score);

		points.setPosition(900*0.2, 10);
	}
	/*load_hp() takes an integer as an argument and converts the number to a string, later to be transformed into a Text object
	//To be printed on the screen*/
	void load_hp(int m)
	{
		std::string life;
		std::ostringstream translate;
		translate << m;
		life = translate.str();

		health.setFont(font);
		health.setCharacterSize(20);
		health.setString(" HP:"+life);

		health.setPosition(900*0.65, 10);

	}
	/*load_lives() takes an integer as an argument and converts the number to a string, later to be transformed into a Text object
	//To be printed on the screen*/
	void load_lives(int l)
	{
		std::string soul;
		std::ostringstream translate;
		translate << l;
		soul = translate.str();

		lives.setFont(font);
		lives.setCharacterSize(20);
		lives.setString(" Lives:" + soul);

		lives.setPosition(900*0.8, 10);
	}


	//index relative to the only flower that wont be empty
	//this function will change the textures of all the flowers to make them look empty, 
	//while only one will look full of polen
	void setEmptyFlowers(int index_full)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == index_full)
			{
				flowers[i].setTexture(&flower_tex[i]);
			}
			else
			{
				flowers[i].setTexture(&flower_empty[i]);
			}
		}
	}

	//Sets the '+1' sprite next to the flower everytime it is called (when the player harvests a flower)
	void loadScoreSprite(int flower_index)
	{
		//sprite_score.setSize(sf::Vector2f(30, 30));		
		sprite_score.setTexture(plus_one);
		tempXflower = (float)flowers[flower_index].getPosition().x + 50;
		tempYflower = (float)flowers[flower_index].getPosition().y;
		sprite_score.setPosition((float)tempXflower, (float)tempYflower);
		//std::cout << "tempXflower: " << tempXflower << " tempYflower: " << tempYflower <<"\n";
		
	}

	void loadSpecialSprite(int x, int y, int sprite_id)
	{
		
		bonus_rectangle.setPosition(x, y);

		switch (sprite_id)
		{
			//////////Heart
			//+5 HP
		case 0:
			bonus_rectangle.setTexture(special_sprites[0]);
			break;

			//+1 UP
		case 1:
			bonus_rectangle.setTexture(special_sprites[1]);
			break;

			//+20
		case 2:
			bonus_rectangle.setTexture(special_sprites[2]);
			break;

			/////////Time
			//+10s
		case 3:
			bonus_rectangle.setTexture(special_sprites[3]);
			break;

			////////Acid Rain
			//-1 UP
		case 4://Bee's soul lifts
			//facing left
			bonus_rectangle.setTexture(special_sprites[4]);
			break;

		case 5://Bee's soul lifts
			//facing right
			bonus_rectangle.setTexture(special_sprites[5]);
			break;

			////////Popsicle
			//+50
		case 6:
			bonus_rectangle.setTexture(special_sprites[6]);
			break;

		deafault:
			break;

		}
	}
	/*loads the water drop image to a sprite that can be moved.
	depending on what the parameter value is, it can also load water drops with an item inside*/
	void loadRain(int n)
	{
		if (n == 0)
		rainSprite.setTexture(water_drop);
	
		
	}

	void rainPosition(int x, int y)
	{
		rainSprite.setPosition((int)x,(int)y);
	}
	//make the rectangle container move downwards by 1 pixel everytime it is called , simulating rain
	
	void show_popsicle()
	{
		background.setTexture(&summer_special);
	}

	void cover_popsicle()
	{
		background.setTexture(&summer);
	}
	
};
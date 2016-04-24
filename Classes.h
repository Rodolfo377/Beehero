#include <time.h>
#include <iostream>
#include "Methods.h"
#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif


class Flowers
{
public:
	Methods m;
public:
	int polen = 7;
	bool ripe = false;

	void setValues(const int input1,  const bool input2)
	{
		polen = input1;
		
		ripe = input2;
	}

	//methos will be called every time the player presses SPACE
	void harvest()
	{
		if (polen > 1)
		{
			polen--; 
			ripe = true;			
		}
		else
		{			
			ripe = false;
		}		
	}

};

class Bees
{
private:
	int score = 0;
	int hp = 10;
	int lives = 1;
public:
	void add_points(const int plus)
	{
		score += plus;
	}
	int getPoints()
	{
		return score;
	}
	void setPoints(const int x)
	{
		score = x;
	}

	void add_hp(const int x)
	{
		hp += x;
	}
	int get_hp()
	{
		return hp;
	}
	void set_hp(const int y)
	{
		hp = y;
	}
	//adds or takes lives
	void alter_lives(const int offset)
	{
		lives += offset;
	}
	int getLives()
	{
		return lives;
	}

};


/*Class Window includes a set of methods and variables that are very useful building a window.
For example, method 'write' takes a string and integer values as coordinates in order to place 
a Text object in the window */
class StandartWindow
{
protected:
	sf::Font pixel8bit;
	sf::Text pressKey;
	Methods blink;
	bool visible;
	sf::Texture pixel_honey_comb;
	sf::RectangleShape background;

	StandartWindow()
	{
		visible = false;
		loadFont();
	}
	

	void loadFont()
	{
		if (pixel8bit.loadFromFile("Fonts/PressStart2P.ttf") == 0)
		{
			std::cout << "Could not find 'PressStart2P.ttf font...\n";
		}
	}

	sf::Text write(std::string str, int x, int y)
	{

		sf::Text text;
		text.setFont(pixel8bit);
		text.setCharacterSize(20);
		text.setString(str);
		text.setPosition((int)x, (int)y);
		text.setColor(sf::Color::Color(128,7,142,255));

		return text;

	}

	//Makes the Text appear and disappear every second, giving a sense of blinking
	void blink_item()
	{
		if (blink.timer_check() <= 1)
		{
			visible = false;
		}
		if (blink.timer_check() <= 0)
		{
			visible = true;
			blink.reset_timer();
		}
	}

	//converts from int to string
	std::string convert(std::string description, int n)
	{
		/*the convertion has been adapted from http://www.cplusplus.com/articles/D9j2Nwbp/*/
		std::string Result;          // string which will contain the result

		std::ostringstream convert;   // stream used for the conversion

		convert << n;      // insert the textual representation of 'Number' in the characters in the stream

		Result = description + convert.str();

		return Result;
	}

	void loadImage()
	{
		if (pixel_honey_comb.loadFromFile("Images/Scenario/background/pixel_comb.png") == 0)
		{
			std::cout << "'pixel_comb.png' not found...\n";
		}
		background.setTexture(&pixel_honey_comb);
		background.setSize(sf::Vector2f(WIDTH, HEIGHT));
	}
};


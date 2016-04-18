#include <time.h>
#include <iostream>
#include "Methods.h"

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
class Window
{
protected:
	sf::Font pixel8bit;
	sf::Text pressKey;
	Methods blink;
	bool visible;

	Window()
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
		text.setPosition(x, y);
		text.setColor(sf::Color::Magenta);

		return text;

	}


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
};


#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#ifndef SIZE
#define SIZE 4
#endif

/*class Menu is responsible for displaying the Menu window and all 
of its contents, besides implementing its interactions

Honey comb image downloaded from https://openclipart.org/detail/176455/honeycomb */

class Menu
{
	//const int SIZE = 4;
	sf::Texture honeyCells;
	sf::Texture vanGogh;
	sf::RectangleShape background;
	sf::RectangleShape menuItems;
	sf::Font pixel8bit;
	sf::Text message[SIZE];
	sf::Sound select;
	sf::Sound click;
	sf::SoundBuffer sel_menu;
	sf::SoundBuffer cli_menu;
	int button_id = -1;


public:
	Menu()
	{
		sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
		window.setFramerateLimit(60);

		sf::Event event;

		loadImages();
		loadFont();

		if (sel_menu.loadFromFile("Sound/menu_select.wav") == 0)
		{
			std::cout << "'menu_select.wav' not found...\n";
		}
		if (cli_menu.loadFromFile("Sound/menu_click.wav") == 0)
		{
			std::cout << "'click_select.wav' not found...\n";
		}

		click.setBuffer(cli_menu);
		select.setBuffer(sel_menu);

		write("Play", 0, 255, 150);
		write("Tutorial", 1, 50, 240);
		write("Ranking", 2, 225, 340);
		write("Quit", 3, 85, 430);
		
		/*item_id: This variable stores the identification of the menu item, which áre the 4 buttons on the menu*/
		int item_id = -1;
		/*select_counter: will serve as a control variable so that when a menu item 
		is pointed at by the cursor, it plays a sound only once*/
		int select_counter = 0;
		/*click_counter: will serve as a control variable so that when a menu item
		is pointed at by the cursor, it plays a sound only once*/
		int click_counter = 0;

		while (window.isOpen())
		{
			
			//Events

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//Logic

			/*a and b store the most real-time coordinates of the cursor relative to the game window
			//and are passed as parameters to function check_mouse_position()*/
			int a = sf::Mouse::getPosition(window).x;
			int b = sf::Mouse::getPosition(window).y;

			//std::cout << "a: "<<a << " b: " << b << "\n";
			item_id = check_mouse_position(a, b);

			if (item_id != -1)
			{
				select_counter++;
				message[item_id].setColor(sf::Color::White);
				if (select_counter == 1)
				{
					//play select_menu.wav
					select.play();
				}
			}
			else
			{
				select_counter = 0;
				click_counter = 0;
				for (int k = 0; k < SIZE; k++)
				{
					message[k].setColor(sf::Color::Black);
				}
			}

			// left click...
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				

				if (item_id != -1)
				{
					click_counter++;
					if (click_counter == 1)
					{
						click.play();
						std::cout << "click\n";

					}
					switch (item_id)
					{
						
					case 0://player clicked on the Play button
						set_button_clicked(0);
						window.close();
						break;
					case 1://player clicked on the Tutorial button
						set_button_clicked(1);
						window.close();
						break;
					case 2://player clicked on the Ranking button
						set_button_clicked(2);
						window.close();
						break;
					case 3://player clicked on the Quit button
						set_button_clicked(3);
						window.close();
						break;
					default:
						break;
					}
					
					
				}
			}
			

			
			//Rendering	
			window.clear();
			window.draw(getBackground());
			window.draw(getCells());

			for (int i = 0; i < SIZE; i++)
			{
				window.draw(message[i]);
			}
			window.display();
		}
	}

	private: 
	void loadImages()
	{
	
		if (honeyCells.loadFromFile("Images/Scenario/background/honey_comb_cells.png") == 0)
		{
			std::cout << "Could not find 'honey_comb_cells.png' image...\n";
		}
		if (vanGogh.loadFromFile("Images/Scenario/background/olive_grove.png") == 0)
		{
			std::cout << "Could not find 'olive_grove.png' image...\n";
		}
			


			menuItems.setSize(sf::Vector2f(424, 600));
			menuItems.setPosition(0, 0);
			menuItems.setTexture(&honeyCells);
		
			background.setSize(sf::Vector2f(1100, 896));
			background.setPosition(0, 0);
			background.setTexture(&vanGogh);
		
	}
	sf::RectangleShape getCells()
	{
		return menuItems;
	}

	sf::RectangleShape getBackground()
	{
		return background;
	}

	void loadFont()
	{
		if (pixel8bit.loadFromFile("Fonts/PressStart2P.ttf") == 0)
		{
			std::cout << "Could not find 'PressStart2P.ttf font...\n";
		}
	}

	//write() does the basic configuration to a given Text object, given by a string.
	sf::Text write(std::string str, int n, int x, int y)
	{
		message[n].setFont(pixel8bit);
		message[n].setCharacterSize(20);
		message[n].setString(str);
		message[n].setPosition(x, y);
		message[n].setColor(sf::Color::Black);

		return message[n];
	}
	//this function will return -1 unless the cursor is positioned over the menu items
	//When the cursor is hovering a menu item, the function will return and integer from 0 to 3 corresponding
	//to the specific item so the player can click it and the program will perform the proper response.
	int check_mouse_position(int a, int b)
	{
		std::cout << "\n\n";
		int chosen = -1;
		
		//positions_array[] will hold the x and y coordinates of the 4 menu items in the following fashion:
		//(x1,y1,x2,y2,x3,y3,x4,y4)
		int positions_array[8];

		//intializes the array members to the relative cordinates of the Text objects that colntain the menu items
		for (int i = 0; i < SIZE; i++)
		{
			positions_array[2*i] = message[i].getPosition().x;
			positions_array[2*i+1] = message[i].getPosition().y;
			//std::cout << positions_array[2 * i] << " " << positions_array[2 * i + 1] << "\n";
		}

		/*checks if the cursor is above any of the items, and assign the index of the item to the local variable 'chosen'
		That will be later assigned to 'item_id' in the menu loop*/
		for (int j = 0; j < SIZE; j++)
		{
			if (a > positions_array[2 * j] && a < positions_array[2 * j] + 150)
			{
				if (b > positions_array[2 * j + 1] && b  < positions_array[2 * j + 1] + 20)
				{
					chosen = j;
				}
			}
		}

		return chosen;
	}

	void set_button_clicked(int x)
	{
		button_id = x;
	}

	public:
	int get_button_clicked()
	{
		
		return button_id;
	}
};
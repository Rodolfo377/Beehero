#include "StartGame.h"
#include "Menu.h"
#include "SplashScreen.h"
#include "HoneyScore.h"
#include "Ranking.h"

int main()
{
	SplashScreen splash;
	//Honey points is the total amount of honey that has been collected on all the stages played
	int honeyPoints = 0;
	Menu myMenu;
	int choice = myMenu.get_button_clicked();
	int response = 0;

	while (choice == -1)
	{
		;
	}

	//Play 
	if (choice == 0)
	{
		
		//One object for each stage of the game

		StartGame start[3];

		//Splash screen
		int i = 0;


		while (i <= 2)
		{
			while (start[i].gameLoop(i + 1) == true)
			{
				;
			}
			//Open another window
			//Amount all the polen into honey
			int hp = start[i].getBeeHP();
			int lives = start[i].getBeeLives();
			int polen = start[i].getBeePolen();

			int round_score = hp*lives*polen;

			
			honeyPoints += round_score;
			

			HoneyScore hs(hp, lives, polen);

			i++;
		}
		
	}

	//Tutorial
	else if (choice == 1)
	{
		std::cout << "player clicked on the Tutorial button\n";
	}
	else if (choice == 2)
	{
		std::cout << "player clicked on the Ranking button\n";
	}
	else if (choice == 3)
	{
		std::cout << "player clicked on the Quit button\n";
	}
	/*
	
	//special stage ... Bet yOu wOnt diScover...
	
	*/
	//Update high score
	Ranking r(honeyPoints);

	return 0;
}
#include "StartGame.h"
#include "Menu.h"
#include "SplashScreen.h"
#include "HoneyScore.h"

int main()
{
	SplashScreen splash;

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

			/*std::cout << "hp: " << hp << " lives: " << lives << " polen: " << polen << "this round's score: " << round_score;
			honeyPoints += round_score;
			std::cout << "\n***********Honey Points in round " << i << ": " << honeyPoints << "***********\n";*/

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

	return 0;
}
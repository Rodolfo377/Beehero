#include "StartGame.h"
#include "Menu.h"
#include "SplashScreen.h"
#include "HoneyScore.h"
#include "Ranking.h"
#include "Tutorial.h"

#include <SFML/Audio.hpp>

int main()
{
	SplashScreen splash;
	//Honey points is the total amount of honey that has been collected on all the stages played
	int honeyPoints = 0;

	int response = 0;
	bool open = true;
	
	sf::Music intro;
	sf::Music stage1;
	sf::Music stage2;
	sf::Music stage3;


		/*Music copied from https://www.youtube.com/watch?v=RGx8_WH43s0 
		Remake of original "Don't stop me now", by Queen*/
		if (intro.openFromFile("Music/BeeHero_Music/intro.wav") == 0)
		{
			std::cout << " 'intro.wav' not found... ";
		}

		intro.setLoop(true);
		intro.play();

		
		/* Music copied from https://www.youtube.com/watch?v=FjNnFlXR9D4
		Remake of original "What does the fox say?", by Ylvis*/
		if (stage1.openFromFile("Music/BeeHero_Music/stage1.wav") == 0)
		{
			std::cout << " 'stage1.wav' not found... ";
		}
		/* Music copied from https://www.youtube.com/watch?v=2RK8W5Uxakc
		Remake of original "Radioactive", by Imagine Dragons*/
		if (stage2.openFromFile("Music/BeeHero_Music/stage2.wav") == 0)
		{
			std::cout << " 'stage2.wav' not found... ";
		}

		/* Music copied from https://www.youtube.com/watch?v=rIlD1mePllA
		Remake of original "Timber", by Kesha feat. Pitbull*/
		if (stage3.openFromFile("Music/BeeHero_Music/stage3.wav") == 0)
		{
			std::cout << " 'stage3.wav' not found... ";
		}
	
	
	while (open)
	{
		
		Menu myMenu;
		int choice = myMenu.get_button_clicked();
		
		
		while (choice == -1)
		{
			;
		}

		//Play 
		if (choice == 0)
		{
			intro.stop();
			//One object for each stage of the game

			StartGame start[3];

			//Splash screen
			int i = 0;


			while (i <= 2)
			{
				if (i == 0)
				{					
					stage1.play();
					stage1.setLoop(true);
				}
				if (i == 1)
				{
					stage1.stop();
					stage2.play();
					stage2.setLoop(true);
				}
				if (i == 2)
				{
					stage2.stop();
					stage3.play();
					stage3.setLoop(true);
				}

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


				HoneyScore hs(hp, lives, polen, honeyPoints);

				i++;
			}
			stage3.stop();
			intro.play();
			Ranking r(honeyPoints);

		}

		//Tutorial
		else if (choice == 1)
		{
			//std::cout << "player clicked on the Tutorial button\n";
			Tutorial();
		}
		else if (choice == 2)
		{
			//std::cout << "player clicked on the Ranking button\n";
			Ranking r(honeyPoints);

		}
		else if (choice == 3)
		{
			//std::cout << "player clicked on the Quit button\n";
			open = false;
		}
}
	/*
	
	//special stage ... Bet yOu wOnt diScover...
	
	*/
	//Update high score
	

	return 0;
}

void loadSoundtrack()
{

}
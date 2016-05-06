#include "StartGame.h"
#include "Menu.h"
#include "SplashScreen.h"
#include "HoneyScore.h"
#include "Ranking.h"
#include "Tutorial.h"
#include "Final_Screen.h"

#include <SFML/Audio.hpp>

int main()
{
	SplashScreen splash;
	//Honey points is the total amount of honey that has been collected on all the stages played
	int honeyPoints = 0;
	int round_score[3];
	int response = 0;
	bool open = true;
	
	sf::Music intro;
	sf::Music stage1;
	sf::Music stage2;
	sf::Music stage3;


	/*Loading the game's soundtracks from the files included with the project*/

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
		//Every time the while(open) loop repeats, i.e. the player closes either the actual game,
		//the ranking or the tutorial window, a Menu object is created, so the result is that the player 
		//can still find the menu aferwards. The Menu object is destroyed when the player select an option
		//from it.
		Menu myMenu;

		//choice represents which option was chosen from the menu, so the code can then perform the proper commands
		int choice = myMenu.get_button_clicked();
	

		//Play 
		if (choice == 0)
		{
			intro.stop();
			//One object for each stage of the game

			//Three StartGame objects are created so each time a round is over there is a new one ready to be launched.
			//The index of the StartGame array is crucial to the game's funcionality.
			StartGame start[3];

			
			int i = 0;

			//controlling each stage soundtrack
			while (i <= 2)
			{
				if (i == 0)
				{					
					stage1.play();
					stage1.setVolume(30);
					stage1.setLoop(true);
				}
				if (i == 1)
				{
					stage1.stop();
					stage2.play();
					stage2.setVolume(30);
					stage2.setLoop(true);
				}
				if (i == 2)
				{
					stage2.stop();
					stage3.play();
					stage3.setVolume(30);
					stage3.setLoop(true);
				}

				//Starts the game
				while (start[i].gameLoop(i + 1) == true)
				{
					;
				}
			
				int hp = start[i].getBeeHP();
				int lives = start[i].getBeeLives();
				int polen = start[i].getBeePolen();

				 round_score[i] = hp*lives*polen;
				 

				honeyPoints += round_score[i];

				//Open another window
				//that will amount all the polen into honey
				HoneyScore hs(hp, lives, polen, round_score[i]);

				i++;
			}
			stage3.stop();
			intro.play();

			//It all comes to this! all of the scores from every round is summed up and the player is given 
			//a special message for his result. The scores are sent separetely in the form of an array.
			Winter w(round_score);

			//Checks if the player's performance is worth joining the local top 5.
			//Updates top scores if so.
			Ranking r(honeyPoints);

		}//choice == 0 (Play)

		//opens Tutorial
		else if (choice == 1)
		{
			
			Tutorial();
		}
		//opens Ranking
		else if (choice == 2)
		{
			//std::cout << "player clicked on the Ranking button\n";
			Ranking r(honeyPoints);

		}
		//terminates the program
		else if (choice == 3)
		{
			//std::cout << "player clicked on the Quit button\n";
			open = false;
		}
}
	
	

	return 0;
}


#include "Base.h"
#include "StartGame.h"

int main()
{
	//One object for each stage of the game
	StartGame start[3];

	//Splash screen
	int i = 1;

	
	while (i <= 3)
	{
		while (start[i-1].gameLoop(i) == true)
		{
			;
		}
		//Open another window
		//Amount all the polen into honey
		i++;
	}
	//special stage ... Bet yOu wOnt diScover...
	

	//Update high score

	return 0;
}
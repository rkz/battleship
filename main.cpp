#ifndef BATTLESHIP_BUILD_TESTS

#include <iostream>
#include <vector>
#include "Game.h"
#include "Grid.h"
#include "LocalPlayer.h"

using namespace std;

int main ()
{
	string name1, name2;
    cout << "Please type players' names." << endl << endl;
    cout << "Player 1: ";
    cin >> name1;
    cout << "Player 2: ";
    cin >> name2;
    cout << endl;
    system("pause");
    
    LocalPlayer* player1 = new LocalPlayer(name1);
    LocalPlayer* player2 = new LocalPlayer(name2);

    Game game = Game(player1, player2);
    game.run();

    delete player1;
    delete player2;

	return 0;
}

#endif

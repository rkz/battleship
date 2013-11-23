#ifndef BATTLESHIP_BUILD_TESTS

#include <iostream>
#include <vector>
#include "Game.h"
#include "Grid.h"
#include "LocalPlayer.h"

using namespace std;

int main ()
{
    
    AbstractPlayer* player1 = new LocalPlayer("Player 1");
    AbstractPlayer* player2 = new LocalPlayer("Player 2");

    Game game = Game(player1, player2);
    game.run();

    delete player1;
    delete player2;

	return 0;
}

#endif

#ifndef BATTLESHIP_BUILD_TESTS

#include <iostream>
#include <vector>
#include "Game.h"
#include "Grid.h"
#include "LocalPlayer.h"

using namespace std;

int main ()
{

    /*Grid g(5);
    g.addShip(Position(2,1), HORIZONTAL, 3, "JCVD");
    g.getCell(Position(2,1))->setStatus(TOUCH); g.getCell(Position(3,1))->setStatus(TOUCH); g.getCell(Position(4,1))->setStatus(TOUCH);
    g.getCell(Position(3,3))->setStatus(WATER);
    cout <<  g;*/
    
    /*LocalPlayer p;
    p.initFleet();*/
    
    AbstractPlayer* player1 = new LocalPlayer();
    AbstractPlayer* player2 = new LocalPlayer();
    Game game = Game(player1, player2);
    game.run();

	return 0;

}

#endif

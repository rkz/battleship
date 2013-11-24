#include "Game.h"

using namespace std;

Game::Game(AbstractPlayer* _player1, AbstractPlayer* _player2)
    : player1(_player1), player2(_player2)
{

}

void Game::run ()
{
    init();
    
    int turnNb = 0;
    bool gameover = false;
    
    while (!gameover)
    {
        if (!(turnNb % 2))
        {
            gameover = turn(player1, player2);
        }
        else
        {
            gameover = turn(player2, player1);
        }
        turnNb++;
    }
    
    if (turnNb % 2)
        cout << "Player1 wins the game!" << endl;
    else
        cout << "Player2 wins the game!" << endl;
}

void Game::init ()
{
    player1->initFleet();
    player2->initFleet();
}

bool Game::turn (AbstractPlayer* toplay, AbstractPlayer* target)
{
    Grid* targetGrid = target->getTargetGrid();
    bool validShot = false;
    bool gameover = false;
    
    while (!validShot)
    {
        Position p = toplay->play(targetGrid);
        ShotResult sr = target->shoot(p);
        validShot = sr.isValid();
        gameover = sr.isWinning();
        toplay->showResult(sr);
    }
    
    return gameover;
}

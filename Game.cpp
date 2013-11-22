#include "Game.h"

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
            gameover = turn(player1, player2);
        else
            gameover = turn(player2, player1);
        turnNb++;
    }
    
    if (turnNb % 2)
        std::cout << "Le joueur 1 a gagné la partie !" << std::endl;
    else
        std::cout << "Le joueur 2 a gagné la partie !" << std::endl;
}

void Game::init ()
{
    player1->initFleet();
    player2->initFleet();
}

bool Game::turn (AbstractPlayer* toplay, AbstractPlayer* target)
{
    Grid* targetGrid = target->getTargetGrid();
    Position p = toplay->play(targetGrid);
    ShotResult sr = target->shoot(p);
    toplay->showResult(sr);
    return sr.isWinning();
}
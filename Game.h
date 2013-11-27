/*
 * Game.h
 *
 * Game représente la partie en cours. Elle possède les deux joueurs (instances d'une
 * classe dérivée de AbstractPlayer qu'elle sollicite successivement selon la séquence
 * de jeu.
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "AbstractPlayer.h"

class Game
{
private:
    AbstractPlayer* player1;
    AbstractPlayer* player2;

public:
	Game (AbstractPlayer* player1, AbstractPlayer* player2);
    void run ();
    void init ();
    bool turn (AbstractPlayer* toplay, AbstractPlayer* target);
    void signature(std::string name) const;
    void finalView(Grid grid1, Grid grid2) const;

};

#endif /* GAME_H_ */

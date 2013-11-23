/*
 * LocalPlayer.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: raphael
 */

#include "LocalPlayer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

LocalPlayer::LocalPlayer()
{
    grid = new Grid(12);
}

LocalPlayer::~LocalPlayer()
{
    delete grid;
}

void LocalPlayer::initFleet()
{
    cout << "Please set your fleet" << endl << endl << "You're going to play with:" << endl;

    placeShip("aircraft carrier", 5);
    placeShip("battleship", 4);
    placeShip("submarine", 3);
    placeShip("destroyer", 3);
    placeShip("patrol boat", 2);
}

void LocalPlayer::placeShip(string name, int length)
{
    system("cls");
    cout << (*grid) << endl;

    cout << "Please place your " << name << "(" << length << ")" << endl << endl;

    // Saisie de la position
    Position pos(-1, -1);
    while (pos == Position(-1, -1)) {
		cout << "Top left position (e.g. A1): ";
		string posString;
		cin >> posString;
		try {
			pos = Position(posString);
		}
		catch (InvalidPositionString& e) {
			cout << "'" << e.what() << "' is not a valid position, please retry." << endl;
		}
    }

    // Saisie de la direction
    string dirString;
    bool firstTry = true;
    while (dirString != "h" && dirString != "H" && dirString != "v" && dirString != "V")
    {
        if (!firstTry)
        {
            cout << "'" << dirString << "' is not a valid direction, please retry (type h or v)." << endl;
        }
        cout << "Direction (h or v): ";
        cin >> dirString;
        firstTry = false;
    }

    Direction dir;
    if (dirString == "h" || dirString == "H") dir = HORIZONTAL;
    else dir = VERTICAL;

    // Placer le bateau
    grid->addShip(pos, dir, length, name);
}

Grid* LocalPlayer::getTargetGrid()
{
	// Risque de fuite mémoire (a priori minime)
    return new Grid (grid->getTargetGrid());
}

Position LocalPlayer::play(Grid* targetGrid)
{
    system("cls");
    string targetString;
    
    cout << "Target grid :" << endl;
    cout << (*targetGrid) << endl;
    cout << "Which position do you want to shoot?" << endl;
    cout << "E.g. 'A1' for top left position: ";
    cin >> targetString;
    cout << endl;
    
    return Position(targetString);
}

ShotResult LocalPlayer::shoot(Position p)
{
    return *grid->shoot(p);
}

void LocalPlayer::showResult(ShotResult sr)
{
    cout << "Result: " << sr.getResultAsString() << endl;
    cout << "Target grid:" << endl;
    sr.printTargetGrid();
}

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

LocalPlayer::LocalPlayer (string _name) : name(_name)
{
    grid = new Grid(12);
}

LocalPlayer::~LocalPlayer()
{
    delete grid;
}

void LocalPlayer::initFleet()
{
	system("cls");
	printInitFleetTitle();

    cout << "Please set your fleet." << endl << endl;
    cout << "In the next screens, please place your ships in the following order:" << endl;
    cout << "    - 1 aircraft carrier (5 cells)" << endl;
    cout << "    - 1 battleship (4 cells)" << endl;
    cout << "    - 1 submarine (3 cells)" << endl;
    cout << "    - 1 destroyer (3 cells)" << endl;
    cout << "    - 1 patrol boat (2 cells)" << endl << endl;

    system("pause");

    while (!placeShip("aircraft carrier", 5)) {}
    while (!placeShip("battleship", 4)) {}
    while (!placeShip("submarine", 3)) {}
    while (!placeShip("destroyer", 3)) {}
    while (!placeShip("patrol boat", 2)) {}

    system("cls");
    printInitFleetTitle();

    cout << (*grid) << endl;

    cout << "Your grid is ready." << endl;
    system("pause");
}

void LocalPlayer::printInitFleetTitle ()
{
	cout << name << ": fleet initialization" << endl;
	cout << "--------------------------------------------------" << endl << endl;
}

bool LocalPlayer::placeShip(string name, int length)
{
    system("cls");
    printInitFleetTitle();

    cout << (*grid) << endl;

    cout << "Please place your " << name << " (" << length << "cells" << ") " << endl << endl;

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
    try {
        grid->addShip(pos, dir, length, name);
        cout << endl << "OK." << endl << endl;
        return true;
    }
    catch (ShipOutOfGridException& e) {
        cout << " Ship out of grid, please retry." << endl;
        system("pause");
        return false;
    }
    catch (ShipCollisionException& e) {
        cout << "There's already another ship at this position, please retry." << endl;
        system("pause");
        return false;
    }
    catch (ShipNearbyException& e) {
        cout << "There's already another ship too close to this position, please retry" << endl;
        system("pause");
        return false;
    }
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
    cout << *sr.getTargetGrid() << endl;
}

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
    cout << "Please set your fleet" << endl << endl << "You're going to play with :" << endl;


    placeShip("aircraft carrier", 5);
    placeShip("battleship", 4);
    placeShip("submarine", 3);
    placeShip("destroyer", 3);
    placeShip("patrol boat", 2);
}

void LocalPlayer::placeShip(string name, int length)
{
    system("cls");
    string posString;
    string dirString;

    cout << (*grid) << endl << endl;
    cout << "Place your " << name << "( " << length << ")" << endl;
    cout << "Top left Position (example A1): ";
    cin >> posString;
    cout << endl;
    bool firstTime = true;
    while (dirString != "h" && dirString != "H" && dirString != "v" && dirString != "V")
    {
        if(firstTime)
        {
            cout << "For Horizontal, please press 'h' and for Vertical press 'v'" << endl;
        }
        cout << "Direction (h/v): ";
        cin >> dirString;
        firstTime = false;
    }

    if (dirString == "h" || dirString == "H")
    {
       grid->addShip(Position(posString), HORIZONTAL, length, name);
    }
    else if (dirString == "v" || dirString == "V")
    {
        grid->addShip(Position(posString), VERTICAL, length, name);
    }

}

Grid* LocalPlayer::getTargetGrid()
{

}

Position LocalPlayer::play(Grid* targetGrid)
{

}

ShotResult LocalPlayer::shoot(Position p)
{

}

void LocalPlayer::showResult(ShotResult sr)
{

}

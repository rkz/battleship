#ifndef BATTLESHIP_BUILD_TESTS

#include <iostream>
#include <vector>
#include "Game.h"
#include "Grid.h"
#include "LocalPlayer.h"
#include <cstdlib>

using namespace std;

enum BattleshipMode
{
	LOCAL,
	NETWORK_CLIENT,
	NETWORK_SERVER
};

class UnknownMode : public exception {};

BattleshipMode getMode (int argc, char** argv)
{
	if (argc < 2) throw UnknownMode();

	string mode(argv[1]);
	if (mode == "local") return LOCAL;
	else if (mode == "client") return NETWORK_CLIENT;
	else if (mode == "server") return NETWORK_SERVER;
	else throw UnknownMode();
}

int main (int argc, char** argv)
{
	try
	{
		BattleshipMode mode = getMode(argc, argv);

		if (mode == LOCAL)
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

		if (mode == NETWORK_CLIENT)
		{
			cout << "Network client mode is not implemented yet!" << endl;
			return 0;
		}

		if (mode == NETWORK_SERVER)
		{
			cout << "Network server mode is not implemented yet!" << endl;
			return 0;
		}
	}
	catch (UnknownMode&)
	{
		cout << "Usage: battleship <mode>" << endl << endl
		     << "Supported modes:" << endl
		     << "    local -- Both players play on this computer." << endl
		     << "    client -- Network mode / client." << endl
		     << "    server -- Network mode / server." << endl;
		exit(1);
	}
}

#endif

#ifdef BATTLESHIP_BUILD_TESTS

#include <boost/test/unit_test.hpp>

#include "Position.h"
#include "Cell.h"
#include "Grid.h"
#include "Ship.h"

BOOST_AUTO_TEST_CASE( grid_create )
{
	Grid g(10);
	BOOST_CHECK(g.getSize() == 10);

	BOOST_CHECK( g.isPositionValid(Position(0, 0)) );
	BOOST_CHECK( g.isPositionValid(Position(9, 9)) );
	BOOST_CHECK( !g.isPositionValid(Position(10, 10)) );
}

BOOST_AUTO_TEST_CASE( grid_addShip )
{
	Grid g(10);

	// créer un bateau
	Ship* s = g.addShip(Position(1, 1), HORIZONTAL, 3, "test ship");
	BOOST_CHECK( s->getCells().size() == 3 );

	// contrôler les cases de ce bateau
	BOOST_CHECK( g.getShipAtPosition(Position(1, 1)) != 0 );
	BOOST_CHECK( g.getShipAtPosition(Position(2, 1)) != 0 );
	BOOST_CHECK( g.getShipAtPosition(Position(3, 1)) != 0 );

	// créer des bateaux "hors grille"
	BOOST_CHECK_THROW( g.addShip(Position(12, 12), HORIZONTAL, 3, "out of grid ship"), ShipOutOfGridException );
	BOOST_CHECK_THROW( g.addShip(Position(1, 2), HORIZONTAL, 20, "super-long ship"), ShipOutOfGridException );

	// créer un bateau en collision
	BOOST_CHECK_THROW( g.addShip(Position(2, 1), VERTICAL, 5, "colliding ship"), ShipCollisionException );
}

BOOST_AUTO_TEST_CASE( grid_get_ship_at_position )
{
	Grid g(10);
    g.addShip(Position(0, 0), HORIZONTAL, 3, "test ship");
	BOOST_CHECK( g.getShipAtPosition(Position(1,0)) !=0 );
	BOOST_CHECK( g.getShipAtPosition(Position(5, 5))==0);
}

BOOST_AUTO_TEST_CASE( grid_get_targetgrid )
{
	Grid g(10);

    g.addShip(Position(0, 0), HORIZONTAL, 3, "test cruiser");
    g.addShip(Position(4, 1), VERTICAL, 5, "test aircraft carrier");

    g.getCell(Position(0, 0))->setStatus(TOUCH);
    g.getCell(Position(1, 0))->setStatus(TOUCH);
    g.getCell(Position(2, 0))->setStatus(TOUCH);

    Grid g1 = g.getTargetGrid();
	BOOST_CHECK( g1.getShipAtPosition(Position(1, 0)) != 0 );
	BOOST_CHECK( g1.getShipAtPosition(Position(4, 3)) == 0 );
}

BOOST_AUTO_TEST_CASE( grid_stringFromGrid_and_gridFromString )
{
	Grid g(3);
    
    g.addShip(Position(0, 0), HORIZONTAL, 3, "submarine");
    
    g.getCell(Position(0, 0))->setStatus(TOUCH);
    g.getCell(Position(1, 0))->setStatus(TOUCH);
    g.getCell(Position(1, 2))->setStatus(WATER);
    
    std::string serial = g.stringFromGrid();
	BOOST_CHECK( serial == "3/TTUUUUUWU/A1H3S" );
}

#endif

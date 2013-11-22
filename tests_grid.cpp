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

	BOOST_CHECK( g.addShip(Position(1, 1), HORIZONTAL, 3, "test ship") );

	BOOST_CHECK( g.getShipAtPosition(Position(1, 1)) != 0 );
	BOOST_CHECK( g.getShipAtPosition(Position(2, 1)) != 0 );
	BOOST_CHECK( g.getShipAtPosition(Position(3, 1)) != 0 );
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
    g.addShip(Position(4,1), VERTICAL, 5, "test aircraft carrier");
    g.getCell(Position(0,0))->setStatus(TOUCH); g.getCell(Position(1,0))->setStatus(TOUCH); g.getCell(Position(2,0))->setStatus(TOUCH);
    Grid g1=g.getTargetGrid();
	BOOST_CHECK( g1.getShipAtPosition(Position(1,0))!=0 );
	BOOST_CHECK( g1.getShipAtPosition(Position(4, 3))==0);
}

#endif

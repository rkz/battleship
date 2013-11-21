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

#endif

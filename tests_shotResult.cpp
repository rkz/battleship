#ifdef BATTLESHIP_BUILD_TESTS

#include <boost/test/unit_test.hpp>

#include "ShotResult.h"
#include "Grid.h"
#include "Position.h"
#include "Cell.h"
#include "Ship.h"

BOOST_AUTO_TEST_CASE( stringFromShotResult )
{
	Grid g(3);

    g.addShip(Position(0, 0), HORIZONTAL, 3, "submarine");

    g.getCell (Position(0, 0))->setStatus(TOUCH);
    g.getCell (Position(1, 0))->setStatus(TOUCH);
    g.getCell (Position(1, 2))->setStatus(WATER);

    ShotResult shot (g, TOUCHED, false);
    std::string serial = shot.stringFromShotResult();
	BOOST_CHECK (serial == "3/TTUUUUUWU/A1H3s$t$f" );

}

BOOST_AUTO_TEST_CASE( ShotResultFromString )
{
    std::string stringToTest= "3/UTUUUUUUU/B1H2p$m$f";
    Grid g(3);
	g.addShip(Position (1,0), HORIZONTAL, 2, "patrol boat");
	g.getCell(Position (1,0))->setStatus(TOUCH);
	ShotResult shot(g, MISSED, false);
	BOOST_CHECK (shot == shotResultFromString(stringToTest));
}

#endif

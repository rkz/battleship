#ifdef BATTLESHIP_BUILD_TESTS

#include <boost/test/unit_test.hpp>

#include "Position.h"
#include "Cell.h"
#include "Grid.h"
#include "Ship.h"

BOOST_AUTO_TEST_CASE( stringFromShotResult )
{
	Grid g(3);
	g.addShip(Position (1,0), HORIZONTAL, 2, "patrol boat");
	g.getCell(Position (1,0))->setStatus(TOUCH);
	ShotResult shot(g, MISSED, false);
	std::string serial = shot.stringFromShotResult();
    BOOST_CHECK (serial == "3/UUUUTUUUU/B1H2p$m$f);
}

BOOST_AUTO_TEST_CASE( ShotResultFromString )
{



}

#endif

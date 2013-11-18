#include <boost/test/unit_test.hpp>

#include "Position.h"
#include "Cell.h"
#include "Grid.h"
#include "Ship.h"

BOOST_AUTO_TEST_CASE( grid_create )
{
	Grid g(10);
	BOOST_CHECK(g.getSize() == 10);
}

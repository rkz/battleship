#include <boost/test/unit_test.hpp>

#include "Position.h"
#include "Cell.h"

BOOST_AUTO_TEST_CASE( position_getX_getY )
{
	Position p(1, 2);
	BOOST_CHECK(p.getX() == 1);
	BOOST_CHECK(p.getY() == 2);
}

BOOST_AUTO_TEST_CASE( position_toString )
{
	Position p(4, 2);
	BOOST_CHECK(p.toString() == "E3");
}

BOOST_AUTO_TEST_CASE( position_fromString )
{
	Position p("C4");
	BOOST_CHECK(p.getX() == 2);
	BOOST_CHECK(p.getY() == 3);
}

BOOST_AUTO_TEST_CASE( position_compare )
{
	Position a(1, 2);
	Position b(1, 2);
	Position c(3, 4);

	BOOST_CHECK(a == b);
	BOOST_CHECK(a != c);
}

BOOST_AUTO_TEST_CASE( position_copy )
{
	Position a(1, 2);
	Position b = a;
	BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE( cell_create )
{
	Position p(1, 2);
	Cell c(p);
	BOOST_CHECK(c.getPosition() == p);
	BOOST_CHECK(c.getStatus() == UNKNOWN);
}

BOOST_AUTO_TEST_CASE( cell_change_status )
{
	Cell c(Position(1, 2));
	c.setStatus(TOUCH);
	BOOST_CHECK(c.getStatus() == TOUCH);
}

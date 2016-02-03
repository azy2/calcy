#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test
#include <boost/test/unit_test.hpp>

#include "parser.h"
#include "eval.h"

using namespace std;

BOOST_AUTO_TEST_CASE(universeInOrder)
{
    //   BOOST_CHECK(eval(parse("(+ 1 -1)")) == 0);
    BOOST_CHECK(1 + 1 == 2);
}

#define BOOST_TEST_MODULE Elsdetector_Test
#include <boost/test/unit_test.hpp>

#include <elsdetector.hpp>

using namespace elsd;

BOOST_AUTO_TEST_CASE(StarsImageTest)
    {
    ElsDetector detector;
    detector.run("test/stars.pgm");

    BOOST_CHECK_EQUAL(detector.getEllipses().size(), 16);
    BOOST_CHECK_EQUAL(detector.getLineSegments().size(), 165);
    BOOST_CHECK_EQUAL(detector.getCircles().size(), 321);
    }

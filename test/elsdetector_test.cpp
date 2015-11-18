#define BOOST_TEST_MODULE Elsdetector_Test
#include <boost/test/unit_test.hpp>

#include <elsdpgmfilereader.hpp>
#include <elsdetector.hpp>

using namespace elsd;

BOOST_AUTO_TEST_CASE(StarsImageTest)
    {
    ImageInterface::Ptr image(new ElsdPgmFileReader("test/stars.pgm"));
    ShapesDetectorInterface::Ptr detector(new ElsDetector);
    detector->run(image);

    BOOST_CHECK_EQUAL(detector->getLineSegments().size(), 165);
    BOOST_CHECK_EQUAL(detector->getCircularArcs().size(), 321);
    BOOST_CHECK_EQUAL(detector->getEllipticalArcs().size(), 16);
    }

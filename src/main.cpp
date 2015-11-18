#include <iostream>
#include <fstream>

#include <elsdpgmfilereader.hpp>
#include <elsdetector.hpp>
#include <elsdsvgwriter.hpp>

using namespace std;
using namespace elsd;

int main(int argc, char **argv)
    {
    if (argc < 2)
        cerr << argv[0] << "<image_name.pgm>" << endl;

    string inFile = argv[1];
    string outFile = inFile + ".svg";

    ImageInterface::Ptr image(new ElsdPgmFileReader(inFile));
    ShapesDetectorInterface::Ptr detector(new ElsDetector);
    SvgWriterInterface::Ptr svg(new ElsdSvgWriter);

    detector->run(image);
    svg->setImageSize(image->xsize(), image->ysize());

    svg->addLineSegments(detector->getLineSegments().begin(), detector->getLineSegments().end());
    svg->addArcs(detector->getCircularArcs().begin(), detector->getCircularArcs().end());
    svg->addArcs(detector->getEllipticalArcs().begin(), detector->getEllipticalArcs().end());

    ofstream ofs(outFile, ofstream::out);
    ofs << *svg;
    ofs.close();

    cout << inFile << endl;
    cout << detector->getEllipticalArcs().size() << " elliptical arcs, "
         << detector->getCircularArcs().size() << " circular arcs, "
         << detector->getLineSegments().size() << " line segments"
         << endl;

    return 0;
    }

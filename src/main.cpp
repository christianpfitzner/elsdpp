#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "elsdetector.hpp"
#include "svgwriter.hpp"

using namespace std;
using namespace elsd;

int main(int argc, char **argv)
    {
    if (argc < 2)
        cerr << argv[0] << "<image_name.pgm>" << endl;

    string inFile = argv[1];
    string outFile = inFile + ".svg";

    ElsDetector detector;
    detector.run(inFile.c_str());

    SvgWriter svg(detector.getXsize(), detector.getYsize());
    std::for_each(detector.getLineSegments().begin(), detector.getLineSegments().end(),
        [&](const LineSegment& lineSegment) {
            svg.addLineSegment(lineSegment);
            }
        );
    std::for_each(detector.getCircles().begin(), detector.getCircles().end(),
        [&](const SvgArc& circle) {
            svg.addArc(circle);
            }
        );
    std::for_each(detector.getEllipses().begin(), detector.getEllipses().end(),
        [&](const SvgArc& ellipse) {
            svg.addArc(ellipse);
            }
        );
    ofstream ofs(outFile, ofstream::out);
    ofs << svg;
    ofs.close();

    cout << inFile << endl;
    cout << detector.getEllipses().size() << " elliptical arcs, "
         << detector.getCircles().size() << " circular arcs, "
         << detector.getLineSegments().size() << " line segments"
         << endl;

    return 0;
    }

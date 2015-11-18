#include "elsdsvgwriter.hpp"
#include <algorithm>

using namespace elsd;

namespace {

void serialize(std::ostream &os, const LineSegment& lineSegment)
    {
    os << "<line x1=\"" << lineSegment.startPoint[0]
       << "\" y1=\"" << lineSegment.startPoint[1]
       << "\" x2=\"" << lineSegment.endPoint[0]
       << "\" y2=\"" << lineSegment.endPoint[1]
       << "\" fill=\"none\" stroke =\"green\" stroke-width=\"1\" />" << std::endl;
    }

void serialize(std::ostream &os, const SvgArc& svgArc)
    {
    os <<"<path d=\"M " << svgArc.startPoint[0] << "," << svgArc.startPoint[1] << " A"
       << svgArc.axes[0] << "," << svgArc.axes[1] << " "
       << svgArc.angle << " " << svgArc.largeArcFlag << "," << svgArc.sweepFlag << " "
       << svgArc.endPoint[0] << "," << svgArc.endPoint[1]
       << "\" fill=\"none\" stroke =\"blue\" stroke-width=\"1\" />" << std::endl;
    }
}

std::ostream& ElsdSvgWriter::SvgHeader::serialize(std::ostream &os) const
    {
    using namespace std;
    os << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl
       << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"" << endl
       << " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl
       << "<svg width=\"" << size[0] << "\" height=\"" << size[1] << "\" "
       << "version=\"1.1\"\n xmlns=\"http://www.w3.org/2000/svg\" "
       << "xmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;
    }

void ElsdSvgWriter::setImageSize(unsigned int xsize, unsigned int ysize)
    {
    header.size = { xsize, ysize };
    }

std::ostream& ElsdSvgWriter::serialize(std::ostream &os) const
    {
    header.serialize(os);

    std::for_each(lineSegments.begin(), lineSegments.end(),
        [&](const LineSegment& lineSegment) { ::serialize(os, lineSegment); }
        );

    std::for_each(svgArcs.begin(), svgArcs.end(),
        [&](const SvgArc& svgArc) { ::serialize(os, svgArc); }
        );

    return os;
    }

#include "svgwriter.hpp"

extern "C" {
#include "write_svg.h"
}

SVGWriter::SVGWriter(const std::string& fileName, unsigned int xsize, unsigned int ysize, unsigned int smoothed) :
    svg(init_svg(const_cast<char*>(fileName.c_str()), xsize, ysize)),
    fe(stdout),
    smooth(smoothed)
{
    if (!svg)
        svg = stdout;
}

SVGWriter::~SVGWriter()
{
    if (svg != stdout)
        fclose_svg(svg);
}

void SVGWriter::write(const std::string& text) const
{
    fwrite(text.c_str(), text.size(), sizeof(char), svg);
    fputc('\n', svg);
}

void SVGWriter::writeLineSegment(const LineSegment& lineSegment) const
{
    write_svg_line(svg, const_cast<double*>(lineSegment.data()), smooth);
}

void SVGWriter::writeCircle(const Circle& circle) const
{
    write_svg_circle(fe, svg, const_cast<double*>(std::get<0>(circle).data()), const_cast<int*>(std::get<1>(circle).data()), smooth);
}

void SVGWriter::writeEllipse(const Ellipse& ellipse) const
{
    write_svg_ellipse(fe, svg, const_cast<double*>(std::get<0>(ellipse).data()), const_cast<int*>(std::get<1>(ellipse).data()), smooth);
}

void SVGWriter::writeLineSegments(const std::vector<LineSegment>& lineSegments) const
{
    std::for_each(lineSegments.begin(), lineSegments.end(), [&](const LineSegment& lineSegment) { writeLineSegment(lineSegment);});
}

void SVGWriter::writeCircles(const std::vector<Circle>& circles) const
{
    std::for_each(circles.begin(), circles.end(), [&](const Circle& circle) { writeCircle(circle);});
}

void SVGWriter::writeEllipses(const std::vector<Ellipse>& ellipses) const
{
    std::for_each(ellipses.begin(), ellipses.end(), [&](const Ellipse& ellipse) { writeEllipse(ellipse);});
}

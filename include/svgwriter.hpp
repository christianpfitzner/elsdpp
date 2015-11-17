#ifndef SVGWRITER_H
#define SVGWRITER_H

#include <string>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include "elsdshapes.hpp"
#include <ostream>

namespace elsd {

/** \addtogroup ELSD
 *  @{
 */

class SvgHeader {
public:
    std::array<unsigned int, 2> size;
friend
    std::ostream& operator<<(std::ostream &os, const SvgHeader &self)
        {
        using namespace std;
        os << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl
           << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"" << endl
           << " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl
           << "<svg width=\"" << self.size[0] << "\" height=\"" << self.size[1] << "\" "
           << "version=\"1.1\"\n xmlns=\"http://www.w3.org/2000/svg\" "
           << "xmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;
        }
    };

/*!
 * \brief The SVG Writer of shapes given in ELSD format
 */
class SvgWriter final
    {
public:
    SvgWriter(unsigned int xsize, unsigned int ysize);
        ~SvgWriter();

    /// write multiple line segments in SVG format
    void addLineSegment(const LineSegment& lineSegment) { lineSegments.push_back(lineSegment); }

    /// write multiple circles in SVG format
    void addArc(const SvgArc& svgArc) { svgArcs.push_back(svgArc); }

private:
    std::vector<LineSegment> lineSegments;
    std::vector<SvgArc> svgArcs;
    SvgHeader header;

    friend
    std::ostream& operator<<(std::ostream &os, const SvgWriter &self)
        {
        os << self.header;
        std::for_each(self.lineSegments.begin(), self.lineSegments.end(),
            [&](const LineSegment& lineSegment) { os << lineSegment; }
            );
        std::for_each(self.svgArcs.begin(), self.svgArcs.end(), [&](const SvgArc& svgArc)
            { os << svgArc; }
            );
        return os;
        }
    };

/** @}*/

} // namespace elsd

#endif // SVGWRITER_H

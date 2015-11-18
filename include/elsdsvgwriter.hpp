#ifndef ELSDSVGWRITER_H
#define ELSDSVGWRITER_H

#include "svgwriterinterface.hpp"
#include <vector>

namespace elsd {

/** \addtogroup ELSD
 *  @{
 */

/*!
 * \brief The SVG Writer of shapes given in ELSD format
 */
class ElsdSvgWriter final : public SvgWriterInterface
    {
    struct SvgHeader {
        std::array<unsigned int, 2> size;
        std::ostream& serialize(std::ostream &os) const;
        };

    public:

    typedef ElsdSvgWriter Self;
    typedef std::shared_ptr<Self> Ptr;

    virtual void setImageSize(unsigned int xsize, unsigned int ysize);
    virtual void addLineSegment(const LineSegment& lineSegment) { lineSegments.push_back(lineSegment); }
    virtual void addArc(const SvgArc& svgArc) { svgArcs.push_back(svgArc); }

    private:

    std::ostream& serialize(std::ostream &os) const;

    SvgHeader header;
    std::vector<LineSegment> lineSegments;
    std::vector<SvgArc> svgArcs;
    };

/** @}*/

} // namespace elsd

#endif // ELSDSVGWRITER_H

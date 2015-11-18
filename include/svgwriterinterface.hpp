#ifndef SVGWRITERINTERFACE_H
#define SVGWRITERINTERFACE_H

#include "elsdshapes.hpp"
#include <ostream>
#include <memory>
#include <algorithm>
#include <vector>

namespace elsd {

class SvgWriterInterface
    {
public:

    typedef SvgWriterInterface Self;
    typedef std::shared_ptr<Self> Ptr;

    virtual void setImageSize(unsigned int xsize, unsigned int ysize) = 0;

    /// add line segment to svg
    virtual void addLineSegment(const LineSegment& lineSegment) = 0;

    /// add svg arc to svg
    virtual void addArc(const SvgArc& svgArc) = 0;

    /// add multiple line segments
    virtual void addLineSegments(
        const std::vector<LineSegment>::const_iterator first,
        const std::vector<LineSegment>::const_iterator last)
        {
        std::for_each(first, last,
            [&](const LineSegment &lineSegment)
                {
                this->addLineSegment(lineSegment);
                }
            );
        }

    /// add multiple arcs
    virtual void addArcs(
        const std::vector<SvgArc>::const_iterator first,
        const std::vector<SvgArc>::const_iterator last)
        {
        std::for_each(first, last,
            [&](const SvgArc &arc)
                {
                this->addArc(arc);
                }
            );
        }

private:
    /// serialize svg
    virtual std::ostream& serialize(std::ostream &os) const = 0;

    friend
    std::ostream& operator<<(std::ostream &os, const SvgWriterInterface &self)
        {
        return self.serialize(os);
        }
    };

}

#endif /* SVGWRITERINTERFACE_H */

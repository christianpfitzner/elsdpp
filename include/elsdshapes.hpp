#ifndef ELSDSHAPES_H
#define ELSDSHAPES_H

#include <array>
#include <ostream>

namespace elsd {

    typedef std::array<double, 2> Point;

    struct LineSegment {
        Point startPoint;
        Point endPoint;
        };

    struct SvgArc :  LineSegment {
        Point axes;
        double angle;
        bool largeArcFlag;
        bool sweepFlag;
        };

} // namespace elsd

#endif /* ELSDSHAPES_H */

#ifndef ELSDSHAPES_H
#define ELSDSHAPES_H

#include <array>
#include <ostream>

namespace elsd {

/** \addtogroup ELSD
 *  @{
 */

/// 2-d point definition
typedef std::array<double, 2> Point;

/// line segment
struct LineSegment
    {
    Point startPoint; //!< segment starts at the current point
    Point endPoint;   //!< segment ends at point (x, y)
    };

/**
 * \brief elliptical arc in SVG format
 * \see http://www.w3.org/TR/SVG/paths.html#PathDataEllipticalArcCommands
 */
struct SvgArc :  LineSegment
    {

    /**
     * the ellipse has the two radii (rx, ry)
     */
    Point axes;

    /**
     * the x-axis of the ellipse is rotated by x-axis-rotation
     * relative to the x-axis of the current coordinate system
     */
    double angle;

    /**
     * if largeArcLag is true, then one of the two larger arc sweeps will be chosen
     * otherwise, if largeArcFlag is false, one of the smaller arc sweeps will be chosen
     */
    bool largeArcFlag;

    /**
     * if sweep-flag is true, then the arc will be drawn in a "positive-angle" direction
     * a value of false causes the arc to be drawn in a "negative-angle" direction
     */
    bool sweepFlag;
    };

/** @}*/

} // namespace elsd

#endif /* ELSDSHAPES_H */

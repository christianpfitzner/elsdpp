#ifndef ELSDSHAPES_H
#define ELSDSHAPES_H

#include <array>
#include <ostream>

namespace elsd {
    typedef std::array<double, 2> Point;

    class LineSegment {
    public:
        Point startPoint;
        Point endPoint;
    friend
        std::ostream& operator<<(std::ostream &os, const LineSegment &lineSegment)
            {
            using namespace std;
            os << "<line x1=\"" << lineSegment.startPoint[0]
               << "\" y1=\"" << lineSegment.startPoint[1]
               << "\" x2=\"" << lineSegment.endPoint[0]
               << "\" y2=\"" << lineSegment.endPoint[1]
               << "\" fill=\"none\" stroke =\"green\" stroke-width=\"1\" />" << endl;
            }
        };

    class SvgArc : public LineSegment {
    public:
        Point axes;
        double angle;
        bool largeArcFlag;
        bool sweepFlag;

    friend
        std::ostream& operator<<(std::ostream &os, const SvgArc &arc)
            {
            using namespace std;
            os <<"<path d=\"M "
               << arc.startPoint[0] << ","
               << arc.startPoint[1] << " A"
               << arc.axes[0] << ","
               << arc.axes[1] << " "
               << arc.angle << " "
               << arc.largeArcFlag << ","
               << arc.sweepFlag << " "
               << arc.endPoint[0] << ","
               << arc.endPoint[1] << "\" fill=\"none\" stroke =\"blue\" stroke-width=\"1\" />" << endl;
            }
        };

} // namespace elsd

#endif /* ELSDSHAPES_H */

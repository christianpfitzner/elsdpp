#ifndef SVGWRITER_H
#define SVGWRITER_H

#include <string>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>

/** \addtogroup ELSD
 *  @{
 */

/*!
 * \brief The SVG Writer of shapes given in ELSD format
 */
class SVGWriter final
{
public:

    typedef std::array<double, 5> LineSegment;
    typedef std::tuple < std::array<double, 5>, std::array<int, 8> > Ellipse;
    typedef std::tuple < std::array<double, 5>, std::array<int, 8> > Circle;

    /*!
     * \brief open file name to write shapes to
     * \param fileName file path to open
     * \param xsize image width
     * \param ysize image height
     * \param smoothed smooth parameter, leave default value - this is not tested
     */
    SVGWriter(const std::string& fileName, unsigned int xsize, unsigned int ysize, unsigned int smoothed = 1);
    ~SVGWriter();

    /// write given text to file
    void write(const std::string& text) const;

    /// write one line segment in SVG format
    void writeLineSegment(const LineSegment& lineSegment) const;

    /// write one circle in SVG format
    void writeCircle(const Circle& circle) const;

    /// write one ellipse in SVG format
    void writeEllipse(const Ellipse& ellipse) const;

    /// write multiple line segments in SVG format
    void writeLineSegments(const std::vector<LineSegment>& lineSegment) const;

    /// write multiple circles in SVG format
    void writeCircles(const std::vector<Circle>& circle) const;

    /// write multiple ellipsess in SVG format
    void writeEllipses(const std::vector<Ellipse>& ellipse) const;

private:
    FILE *svg;
    FILE *fe;
    unsigned int smooth;
};

/** @}*/

#endif // SVGWRITER_H

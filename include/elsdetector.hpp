#ifndef ELSDETECTOR_H
#define ELSDETECTOR_H

#include <vector>
#include <array>
#include <tuple>
#include <string>
#include <exception>
#include <memory>

class image_double_s;

/** \addtogroup ELSD
 *  @{
 */

/*!
 * \brief The wrapper class for calling ELSD extraction function
 *
 * \see http://ubee.enseeiht.fr/vision/ELSD/
 */
class ElsDetector final
{
public:
    typedef std::shared_ptr<ElsDetector> Ptr;

    typedef std::array<double, 5> LineSegment;
    typedef std::tuple < std::array<double, 5>, std::array<int, 8> > Ellipse;
    typedef Ellipse Circle;

    /*!
     * \brief initialization of algorithm with default parameters
     *
     * \note use default parameters as they were hardcoded in original algorithm and are not well documented
     *       moreover it is stated in the paper of algorithm's authors that the method is parameterless
     *
     * @param angleTolerance Gradient angle tolerance in degrees
     * @param epsilon not documented
     */
    ElsDetector(double epsilon = 1);
    ~ElsDetector();

    /*!
     * \brief run ELSD extraction on given data
     * \param img image in ELSD format
     */
    void run(image_double_s* const img);

    /*!
     * \brief get all LineSegments detected
     * \return LineSegments in ELSD format
     */
    const std::vector<LineSegment>& getLineSegments() const { return linesegments; }

    /*!
     * \brief get all Circles detected
     * \return Circles in ELSD format
     */
    const std::vector<Circle>& getCircles() const { return circles; }

    /*!
     * \brief get all Ellipses detected
     * \return Ellipses in ELSD format
     */
    const std::vector<Ellipse>& getEllipses() const { return ellipses ; }

private:
    unsigned int xsize;
    unsigned int ysize;

    std::vector<LineSegment> linesegments;
    std::vector<Circle> circles;
    std::vector<Ellipse> ellipses;

    const double p;
    const double eps;
};

/** @}*/

#endif // ELSDETECTOR_H

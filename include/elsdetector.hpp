#ifndef ELSDETECTOR_H
#define ELSDETECTOR_H

#include <vector>
#include <array>
#include <tuple>
#include <string>
#include <exception>
#include <memory>
#include "elsdshapes.hpp"

extern "C" {
    struct image_double_s;
    }

namespace elsd {

/** \addtogroup ELSD
 *  @{
 */

class ImageInterface {
public:
    virtual int xsize() const = 0;
    virtual int ysize() const = 0;
    virtual unsigned char pixel(int ypos, int xpos) const = 0;
    };

/*!
 * \brief The wrapper class for calling ELSD extraction function
 *
 * \see http://ubee.enseeiht.fr/vision/ELSD/
 */
class ElsDetector final
{
public:
    typedef std::shared_ptr<ElsDetector> Ptr;

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
    void run(const char* PGMfilename);
    void run(const ImageInterface& img);

    /*!
     * \brief get all LineSegments detected
     * \return LineSegments in ELSD format
     */
    const std::vector<LineSegment>& getLineSegments() const { return linesegments; }

    /*!
     * \brief get all Circles detected
     * \return Circles in ELSD format
     */
    const std::vector<SvgArc>& getCircles() const { return circles; }

    /*!
     * \brief get all Ellipses detected
     * \return Ellipses in ELSD format
     */
    const std::vector<SvgArc>& getEllipses() const { return ellipses ; }

    unsigned int getXsize() const { return xsize*1.25; };
    unsigned int getYsize() const { return ysize*1.25; };

private:
    void run(const image_double_s *img);

    unsigned int xsize;
    unsigned int ysize;

    std::vector<LineSegment> linesegments;
    std::vector<SvgArc> circles;
    std::vector<SvgArc> ellipses;

    const double p;
    const double eps;
};

/** @}*/

} // namespace elsd

#endif // ELSDETECTOR_H

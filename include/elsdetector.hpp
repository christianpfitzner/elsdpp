#ifndef ELSDETECTOR_H
#define ELSDETECTOR_H

#include "shapesdetectorinterface.hpp"

namespace elsd {

/** \addtogroup ELSD
 *  @{
 */

/*!
 * \brief The wrapper class for calling ELSD extraction function
 *
 * \see http://ubee.enseeiht.fr/vision/ELSD/
 */
class ElsDetector final : public ShapesDetectorInterface
    {
public:
    typedef ElsDetector Self;
    typedef std::shared_ptr<Self> Ptr;

    virtual void run(const ImageInterface::Ptr img);

    virtual const std::vector<LineSegment>& getLineSegments() const { return lineSegments; }
    virtual const std::vector<SvgArc>& getCircularArcs() const { return circularArcs; }
    virtual const std::vector<SvgArc>& getEllipticalArcs() const { return ellipticalArcs; }

private:
    std::vector<LineSegment> lineSegments;
    std::vector<SvgArc> circularArcs;
    std::vector<SvgArc> ellipticalArcs;
};

/** @}*/

} // namespace elsd

#endif // ELSDETECTOR_H

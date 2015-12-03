#ifndef SHAPESDETECTORINTERFACE_H
#define SHAPESDETECTORINTERFACE_H

#include "imageinterface.hpp"
#include "elsdshapes.hpp"
#include <memory>
#include <vector>

namespace elsd {

/** \addtogroup ELSD
 *  @{
 */

/**
 * \brief detect all line segments and elliptical arcs in the given image
 */
class ShapesDetectorInterface
    {
public:
    typedef ShapesDetectorInterface Self;
    typedef std::shared_ptr<Self> Ptr;

    /// run the algorthm on given image
    virtual void run(const ImageInterface::Ptr img) = 0;

    /// get ref. to vector of all line segments detected
    virtual const std::vector<LineSegment>& getLineSegments() const = 0;

    /// get ref. to vector of all circular arcs detected
    virtual const std::vector<SvgArc>& getCircularArcs() const = 0;

    /// get ref. to vector of all elliptical arcs detected
    virtual const std::vector<SvgArc>& getEllipticalArcs() const = 0;
    };

/** @}*/

} // namespace elsd

#endif /* SHAPESDETECTORINTERFACE_H */

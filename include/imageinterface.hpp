#ifndef IMAGEINTERFACE_H
#define IMAGEINTERFACE_H

#include <memory>

/** \addtogroup ELSD
 *  @{
 */

namespace elsd {

/**
 * \brief gray-level 8-bit image interface
 */

class ImageInterface {
public:
    typedef ImageInterface Self;
    typedef std::shared_ptr<Self> Ptr;

    /// get image width
    virtual int xsize() const = 0;

    /// get image height
    virtual int ysize() const = 0;

    /// get image value at (ypos, xpos) point
    virtual unsigned char pixel(int ypos, int xpos) const = 0;
    };

} // namespace elsd

/** @}*/

#endif /* IMAGEINTERFACE_H */

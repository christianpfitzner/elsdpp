#ifndef IMAGEINTERFACE_H
#define IMAGEINTERFACE_H

#include <memory>

class ImageInterface {
public:
    typedef ImageInterface Self;
    typedef std::shared_ptr<Self> Ptr;

    virtual int xsize() const = 0;
    virtual int ysize() const = 0;
    virtual unsigned char pixel(int ypos, int xpos) const = 0;
    };

#endif /* IMAGEINTERFACE_H */

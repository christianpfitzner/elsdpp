#ifndef ELSDPGMFILEREADER_H
#define ELSDPGMFILEREADER_H

#include "imageinterface.hpp"
#include <string>

extern "C" {
    struct image_double_s;
}

namespace elsd {

// read PGM file - ELSD specific feature
class ElsdPgmFileReader final : public ImageInterface
    {
    public:

    typedef ElsdPgmFileReader Self;
    typedef std::shared_ptr<Self> Ptr;

    ElsdPgmFileReader(const std::string &filename);
    ~ElsdPgmFileReader();

    virtual int xsize() const;
    virtual int ysize() const;
    virtual unsigned char pixel(int ypos, int xpos) const;

    private:

    image_double_s *image;
    };

} // namespace elsd

#endif /* ELSDPGMFILEREADER_H */

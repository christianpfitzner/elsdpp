#include <elsdpgmfilereader.hpp>
#include <stdexcept>

extern "C" {
#include "elsd.h"
}

using namespace elsd;
using namespace std;

ElsdPgmFileReader::ElsdPgmFileReader(const string &filename)
    {
    image = read_pgm_image_double(filename.c_str());
    if (image == NULL)
        throw runtime_error("Could not open file");
    }

ElsdPgmFileReader::~ElsdPgmFileReader()
    {
    free_image_double(image);
    }

int ElsdPgmFileReader::xsize() const
    {
    return image->xsize;
    }

int ElsdPgmFileReader::ysize() const
    {
    return image->ysize;
    }

unsigned char ElsdPgmFileReader::pixel(int ypos, int xpos) const
    {
    if (xpos >= xsize())
        throw invalid_argument("X size");

    if (ypos >= ysize())
        throw invalid_argument("Y size");

    return image->data[xpos + ypos * xsize()];
    }

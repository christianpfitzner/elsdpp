#include "svgwriter.hpp"

using namespace elsd;

SvgWriter::SvgWriter(unsigned int xsize, unsigned int ysize)
    {
    header.size = { xsize, ysize };
    }

SvgWriter::~SvgWriter()
    {
    }


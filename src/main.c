#include "elsd.h"
#include <math.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  double quant = 2.0; /* Bound to the quantization error on the
                         gradient norm. */
  double ang_th = 22.5; /* Gradient angle tolerance in degrees. */
  double p = ang_th/180.0;
  double prec = M_PI*ang_th/180.0; /* radian precision */
  double rho = quant/sin(prec);
  double eps = 1; /* atof(argv[2]); */
  int smooth = 1; /* atoi(argv[3]); */
  int ell_count = 0, line_count = 0, circ_count = 0;
  image_double image;
  char *image_filename = NULL;
  if (argc < 2)
    error("%s : ./elsd <image_name.pgm>", argv[0]);
  image_filename = argv[1];

  image = read_pgm_image_double(image_filename);
  EllipseDetection(image,
                   rho,
                   prec,
                   p,
                   eps,
                   smooth,
                   &ell_count,
                   &circ_count,
                   &line_count,
                   image_filename);

  printf("%s\n", image_filename);
  printf("%d elliptical arcs, %d circular arcs, %d line segments\n",
         ell_count, circ_count, line_count);

  return 0;
}

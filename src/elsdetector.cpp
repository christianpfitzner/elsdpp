#include <boost/format.hpp>
#include "elsdetector.hpp"

extern "C" {
#include "elsd.h"
#include "process_curve.h"
#include "process_line.h"
#include "valid_curve.h"
}

ElsDetector::ElsDetector(double epsilon) :
    xsize(0),
    ysize(0),
    p(1./8.),
    eps(epsilon)
{
//    static const double angleTolerance = 2;
}

ElsDetector::~ElsDetector()
{
}

void ElsDetector::run(image_double_s* const img)
{
    static const double prec = M_PI*p;
    // quantizationError Bound to the quantization error on the gradient norm
    // because of quantization to {0 ... 255} the maximal possible error in the gradient is 1
    // when adjecent pixels have quantization errors of 0.5 that do not compensate
    // for empirical reasons, we preffered a more conservative bound and we set:
    static const double quantizationError = 2.0;
    double gradient_angle_error = quantizationError/sin(prec);

    image_double angles,gradx,grady,grad,image;
    image_char used;
    void *mem_p;
    int n_bins = 1024;
    double max_grad = 255.0;
    struct coorlist *list_p;
    struct point *reg, *regl;
    struct point3 *regc, *rege;
    struct rect rec;
    int reg_size = 0,regp_size[3];
    int i;
    int min_size[3];
    double logNT[3]; /* number of tests for the 3 primitive types */ 
    double nfa[3]; /* NFA value using the discrete formulation for the three primitive types */
//    double parame[5], paramc[5]; /* ellipse/circle parameters */
//    double lin[5];
    std::array<double, 5> parame;
    std::array<double, 5> paramc; /* ellipse/circle parameters */
    std::array<double, 5> lin;
    std::array<double, 5> linSmooth;
    double density_th = 0.7;
    double mlog10eps = - log10(eps); 
    double reg_angle;
//    int pext[8];
    std::array<int, 8> pext;
    unsigned int xsz0,ysz0;

    xsz0 = img->xsize;
    ysz0 = img->ysize;

    // smoothing preprocessing gaussian smoothing of input image
    // the standard deviation of Gaussian kernel is determined by:
    // \sigma = \Sigma / S, where S is the scaling factor
    // The value of \Sigma is set to 0.6, which gives a good balance
    // between avoiding aliasing and avoiding image bluring
    static const double scale = 0.8;
    static const double sigma_scale = 0.6;
    image = gaussian_sampler(img, scale, sigma_scale);

    angles = ll_angle(image,gradient_angle_error,&list_p,&mem_p,&gradx,&grady,&grad,n_bins,max_grad);

    xsize = angles->xsize;
    ysize = angles->ysize;

    /* number of tests for elliptical arcs */
    logNT[2] = 4.0 *(log10((double)xsize)+log10((double)ysize)) + log10(9.0) + log10(3.0); /* N^8 */
    /* number of tests for circular arcs */
    logNT[1] = 3.0 *(log10((double)xsize)+log10((double)ysize)) + log10(9.0) + log10(3.0); /* N^6 */
    /* number of tests for line-segments */
    logNT[0] = 5.0 *(log10((double)xsize)+log10((double)ysize))/2.0 + log10(11) + log10(3.0); /* N^5 */

    /* thresholds from which an elliptical/circular/linear arc could be meaningful */
    min_size[2] =(int)((-logNT[2]+log10(eps))/log10(p));
    min_size[1] =(int)((-logNT[1]+log10(eps))/log10(p));
    min_size[0] =(int)((-logNT[0]+log10(eps))/log10(p));

    /* allocate memory for region lists */
    reg = (struct point *) calloc(xsize * ysize, sizeof(struct point));
    regl = (struct point *) calloc(xsize * ysize, sizeof(struct point));
    regc = (struct point3 *) calloc(xsize * ysize, sizeof(struct point3));
    rege = (struct point3 *) calloc(xsize * ysize, sizeof(struct point3));
    used = new_image_char_ini(xsize,ysize,NOTUSED);
    
    /* init temporary buffers */
    gBufferDouble = (double*)malloc(sizeof(double));
    gBufferInt    = (int*)malloc(sizeof(int));

    /* begin primitive detection */
    for(;list_p; list_p = list_p->next) { 
        reg_size = 0;
        if(used->data[list_p->y*used->xsize+list_p->x]==NOTUSED &&
            angles->data[list_p->y*angles->xsize+list_p->x] != NOTDEF) {
            /* init some variables */
            for (i=0;i<5;i++) {
                parame[i] = 0.0; paramc[i] = 0.0;
            }
            nfa[2] = nfa[1] = nfa[0] = mlog10eps; 
            reg_size = 1;regp_size[0] = regp_size[1] = regp_size[2] = 0;
            region_grow(list_p->x, list_p->y, angles, reg, &reg_size, &reg_angle,used, prec); 

            /*-------- FIT A LINEAR SEGMENT AND VERIFY IF VALID ------------------- */
            valid_line(reg,&reg_size,reg_angle,prec,p,&rec,lin.data(),grad,gradx,grady, used,angles,density_th,logNT[0],mlog10eps,&nfa[0]);
            regp_size[0] = reg_size;

            for (i=0;i<regp_size[0];i++) {
                regl[i].x = reg[i].x; regl[i].y = reg[i].y;
            }

            if (reg_size>2) {
                /*-------- FIT CONVEX SHAPES (CIRCLE/ELLIPSE) AND VERIFY IF VALID -------- */
                valid_curve(reg,&reg_size,prec,p,angles,used,grad,gradx,grady,paramc.data(),parame.data(),rec,logNT,mlog10eps,density_th,min_size,nfa,pext.data(),regc,rege,regp_size);

                /* ------ DECIDE IF LINEAR SEGMENT OR CIRCLE OR ELLIPSE BY COMPARING THEIR NFAs -------*/
                if(nfa[2]>mlog10eps && nfa[2]>nfa[0] && nfa[2]>nfa[1] && regp_size[2]>min_size[2]) /* ellipse */ {
                    ellipses.push_back(std::make_tuple(parame, pext));
                    for (i=0;i<regp_size[0];i++)
                        used->data[regl[i].y*used->xsize+regl[i].x] = NOTUSED;
                    for (i=0;i<regp_size[1];i++)
                        used->data[regc[i].y*used->xsize+regc[i].x] = NOTUSED;
                    for (i=0;i<regp_size[2];i++)
                        if (rege[i].z == USEDELL) { 
                            used->data[rege[i].y*used->xsize+rege[i].x] = USED;
                        }
                        else { 
                            used->data[rege[i].y*used->xsize+rege[i].x] = USEDELLNA;
                        }
                }
                else if(nfa[1]>mlog10eps && nfa[1]>nfa[0] && nfa[1]>nfa[2] && regp_size[1]>min_size[1]) /* circle */ {
                    circles.push_back(std::make_tuple(paramc, pext));
                    for (i=0;i<regp_size[0];i++)
                       used->data[regl[i].y*used->xsize+regl[i].x] = NOTUSED;
                    for (i=0;i<regp_size[2];i++)
                        used->data[rege[i].y*used->xsize+rege[i].x] = NOTUSED;
                    for (i=0;i<regp_size[1];i++)
                        if (regc[i].z == USEDCIRC)
                            used->data[regc[i].y*used->xsize+regc[i].x] = USED;
                        else 
                            used->data[regc[i].y*used->xsize+regc[i].x] = USEDCIRCNA;
                }
                else if(nfa[0]>mlog10eps && regp_size[0]>min_size[0] && nfa[0]>nfa[1] && nfa[0]>nfa[2]) /* line */ {
                    for (auto i = 0; i < linSmooth.size(); ++i)
                        linSmooth[i] = lin[i]*1.25;
                    linesegments.push_back(linSmooth);
                    for (i=0;i<regp_size[1];i++)
                        used->data[regc[i].y*used->xsize+regc[i].x] = NOTUSED;
                    for (i=0;i<regp_size[2];i++)
                        used->data[rege[i].y*used->xsize+rege[i].x] = NOTUSED;
                    for (i=0;i<regp_size[0];i++)
                        used->data[regl[i].y*used->xsize+regl[i].x] = USED;
                }
                else /* no feature */ {
                    for (i=0;i<regp_size[1];i++)
                        used->data[regc[i].y*used->xsize+regc[i].x] = NOTUSED;
                    for (i=0;i<regp_size[2];i++)
                        used->data[rege[i].y*used->xsize+rege[i].x] = NOTUSED;
                    for (i=0;i<regp_size[0];i++)
                        used->data[regl[i].y*used->xsize+regl[i].x] = NOTUSED;
                }
            }
        }/* IF USED */
    }/* FOR LIST */

    free_image_double(image);
    free_image_double(gradx);
    free_image_double(grady);
    free_image_double(grad);
    free_image_double(angles); 
    free_image_char(used);
    free(reg);
    free(regl);
    free(regc);
    free(rege); 
    free(gBufferDouble);
    free(gBufferInt); 
    free(mem_p);
    }

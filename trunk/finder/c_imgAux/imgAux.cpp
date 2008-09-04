#include <cv.h>
#include <math.h>

 #include <imgAux.hpp>

bool imgAux::issimilar(IplImage* img,int x1,int y1,int x2,int y2,double sim_factor) {

	CvScalar color1, color2;
    int diff, square;
    int sum = 0;
    double result;

    // There is no reason to test right and lower bound
    // because is a 4-narrow search
    if ( x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 )
        return false;

    color1 = cvGet2D(img,x1,y1);
    color2 = cvGet2D(img,x2,y2);	
    int i;
    for (i=0;i<img->nChannels;i++){
        diff = int(color1.val[i] - color2.val[i]);
        square = diff * diff;
        sum = sum + square;
    }

    result = sqrt(sum);
    return (result < sim_factor);
}


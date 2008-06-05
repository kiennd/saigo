#include <cmath>
#include <iostream>
using namespace std;

 #include <image.hpp>

int* Image::histogram ( int color ) 
{
	int i,j,k;
    int *h = new int[maxval + 1];

    for ( i = 0 ; i < (maxval + 1) ; i++ )
        h[i] = 0;

    for ( i = 0 ; i < height ; i++ )
        for ( j = 0 ; j < width ; j++ )
            h[mx[i][j][color]]++;

    return h;
}

// Find the higher sample value in the image
sample Image::higher_val () {
	int i,j,k;
    sample max = 0;
    for ( i = 0 ; i < height ;  i++ )
        for ( j = 0 ; j < width ; j++ )
            for ( k = 0 ; k < depth ; k++ )
                if ( mx[i][j][k] > max )
                    max = mx[i][j][k];

    return max;
}

double Image::psnr ( Image *img2 ) 
{
    double rmse_val, division;

    rmse_val = rmse(img2);
    if ( rmse_val ) {
        division = maxval / rmse_val;
        return 20 * (log10(division));
    } else {
        return 0;
    }
}

double Image::rmse ( Image *img2 ) 
{
	int i, j, k;
    double result,square,diff;
    double sum = 0;

    for (i=0; i < height; i++){
        for (j=0; j < width; j++){
            for (k=0; k < depth; k++){
                diff = mx[i][j][k] - img2->mx[i][j][k];
                square = pow(diff,2);
                sum = sum + square;
            }
        }
    }

    result = sum / (height * width);
    return sqrt(result);
}

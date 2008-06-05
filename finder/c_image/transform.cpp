 #include <image.hpp>

Image* Image::non_linear_transform ( double (*func)(sample) )
{
	// Real Max value of image
    sample fmax = higher_val ();

    // Constant that put 'tgt' in same range of 'src'
    double corrector = fmax / func(fmax) ;

    // Searching greater value that is 0 in resultant transform
    sample fmin = 1;
    while ( fmin <= fmax && (func(fmin) * corrector) < 0.5 )
        fmin++;

    fmin--;

    Image *tgt = new Image(*this);

    int i,j,k;
    double alpha = double(fmax - fmin) / double(fmax);
    double interp_value;
    for ( i = 0 ; i < height ;  i++ )
        for ( j = 0 ; j < width ; j++ )
            for ( k = 0 ; k < depth ; k++ ) {
                // Gets interpoled value of pixel in fmin~fmax interval
                interp_value = fmin + double(mx[i][j][k] * alpha);
                // Apply transformation in interp_value and return rounded value to 'tgt' image
                tgt->mx[i][j][k] = sample((func(sample(interp_value)) * corrector) + 0.5);
            }

    return tgt;
}

Image* Image::linear_transform (double ALPHA , double BETA , double GAMA )
{
	Image *tgt = new Image (*this);
    sample value;

	if ( ALPHA + BETA + GAMA != 3 )
		return NULL;
		

    // Calculate the limits of gray scales
   	sample lim_a = (sample) ((1.0/3.0) * higher_val());
    sample lim_b = (sample) ((2.0/3.0) * higher_val());

    int i,j,k;
    for ( i = 0 ; i < height ; i++ )
        for ( j = 0 ; j < width ; j++ )
            for ( k = 0 ; k < depth ; k++ ) {

                // This verifies which is the corresponding interval and apply the
                // adequate function
                if ( mx[i][j][k] <= lim_a ) {
                    value = sample(mx[i][j][k] * ALPHA);
                } else if ( mx[i][j][k] <= lim_b ) {
                    value = sample( (mx[i][j][k]-lim_a) * BETA + ALPHA * lim_a);
                } else {
                    value = sample( (mx[i][j][k]-lim_b) * GAMA +  BETA * (lim_b-lim_a) + ALPHA * lim_a );
                }

                // Pixel Rounding to sample
                tgt->mx[i][j][k] = sample( value + 0.5 );
            }
    return tgt;
}

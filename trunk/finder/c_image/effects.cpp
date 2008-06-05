 #include <image.hpp>

// Return a image with a rotation of 'img' in 90 degrees to 'side'
void Image::rotate ( int side )
{
	sample ***buf = new sample **[height];
    
	int i,j,k;
	for ( i = 0 ; i < width ; i++ ) {
		buf[i] = new sample*[width];
		for ( j = 0 ; j < height ; j++ ) {
			buf[i][j] = new sample [width];
		}
	}

    for ( j = 0 ; j < width ; j++ ) 
        for ( i = 0 ; i < height ; i++ ) 
            for ( k = 0 ; k < depth ; k++ )
                if ( side == ROTATE_RIGHT )
                    buf[j][(height - 1)-i][k] = mx[i][j][k];
                else
                    buf[(width - 1)-j][i][k] = mx[i][j][k];
		
	mx = buf;	

	int swap_buf = width;
	width =  height;
	height = swap_buf;
}

// Generates a image with color in negative
Image* Image::negative ()
{
    Image *tgt = new Image(*this);

    int i,j,k;

    for ( i = 0 ; i < height ; i++ )
        for ( j = 0 ; j < width ; j++ )
            for ( k = 0 ; k < depth ; k++ )
                tgt->mx[i][j][k] = tgt->maxval - tgt->mx[i][j][k];

    return tgt;
}

Image* Image::dithering ()
{
	Image *dithered = new Image(*this);

	int i,j,k;

	int diff;
	sample value;
	for ( i = 0 ; i < height ; i++ )
		for ( j = 0 ; j < width ; j++ )
			for ( k = 0 ; k < depth ; k++ ) {
				value = dithered->mx[i][j][k] >= (maxval / 2) ? 1 : 0;
				diff = dithered->mx[i][j][k] - ( value * maxval );
	
				dithered->mx[i][j][k] = value;
				
				if ( j-1 >= 0 && i+1 < height )
					 dithered->mx[i+1][j-1][k] = sample(dithered->mx[i+1][j-1][k] + (3.0/16) * diff);	
				
				if ( j+1 < width && i+1 < height ) {
					dithered->mx[i][j+1][k] = sample(dithered->mx[i][j+1][k] + (7.0/16) * diff);	
					dithered->mx[i+1][j][k] = sample(dithered->mx[i+1][j][k] + (5.0/16) * diff);	
					dithered->mx[i+1][j+1][k] = sample(dithered->mx[i+1][j+1][k] + (1.0/16) * diff);
				}
			}
	dithered->maxval = 1;	
	return dithered;
}

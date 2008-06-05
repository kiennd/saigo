 #include <image.hpp>
#include <fstream>
#include <string>
using namespace std;

Image::Image ( string file_name ) 
{
	ifstream fs (file_name.c_str());
	int max_buf;
	
	// Taking out P
	fs.get();

	// Reading Header
	fs >> type >> width >> height >> max_buf;
	maxval = sample(max_buf);
	depth = isppm() ? 3 : 1;

	// Taking out \n
	fs.get();

	mx = new sample**[height];

    int i,j,k;
    for (i = 0 ; i < height ; i++ ) {
        mx[i] = new sample*[width];

        for ( j = 0 ; j < width ; j++ ) {
            mx[i][j] = new sample[depth];

			for ( k = 0 ; k < depth ; k++ ) {

				if ( isplain() ) {
					// Using a integer as swap because
					// the number is in ascii
					int ibuf;
					fs >> ibuf;
					mx[i][j][k] = sample(ibuf);
				} else {
					// Using char as swap because
					// a char has one byte as well as in pnm format
					char s;
					fs.read(&s,sizeof(char));
					mx[i][j][k] = sample(s);
				}
			}
		}
    }
	fs.close();
} 

// Copy Every Atribute of Image
Image::Image ( Image& old )
{
	height = old.height;
	width = old.width;
	depth = old.depth;
	maxval = old.maxval;
	type = old.type;
	mx = new sample** [height];
	
	int i,j,k;
    for (i = 0 ; i < height ; i++ ) {
        mx[i] = new sample*[width];
        for ( j = 0 ; j < width ; j++ ) {
            mx[i][j] = new sample [depth];

			for (k = 0 ; k < depth ; k++ )
				mx[i][j][k] = old.mx[i][j][k];

		}
	}
}

void Image::save ( string file_name )
{
	ofstream fs(file_name.c_str());
	
	// Print Header
	// Max buf is needed because ofstream will print a value
	// with sasmple size, instead of printing a integer.
	int max_buf = int(maxval);
	fs << "P" << type << endl << 
	width << " " << height << endl << 
	max_buf << endl;

	int i,j,k;
	for ( i = 0 ; i < height ; i++ ) {
		for (j = 0 ; j < width ; j++ ) {
			for ( k = 0 ; k < depth ; k++ ) {
				if ( isplain() ) {
					// Format needs an integer
					int ibuf = int(mx[i][j][k]);
					fs << ibuf << ' ' ;
				} else {
					// Using a char to write a byte
					char val = char(mx[i][j][k]);
					fs.write (&val,sizeof(char));
				}
			}
		}
		if ( isplain() ) fs << endl ;
	}
	fs.close();
}

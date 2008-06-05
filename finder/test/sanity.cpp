#include <iostream>
using namespace std;

#include <image.hpp>
#include <cmath>

double foobar ( sample val ) { return pow(double(val),2); }

int main ( int argc , char **argv )
{
	Image teste(argv[1]);

	Image *t = teste.non_linear_transform(foobar);
	Image *d = teste.dithering();

	t->save("bla.pgm");
	d->save("dithered.pgm");
}


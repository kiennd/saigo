 #include <image.hpp>
#include <cmath>

bool Image::isppm () 
{
	return (type == 3 || type == 6);
}

bool Image::isplain ()
{ 
	return (type <= 3);
}


bool Image::issimilar(int x1,int y1, int x2,int y2, double sim_factor)
{
	sample color1, color2;
	int diff, square;
	int sum = 0;
	double result;

	// There is no reason to test right and lower bound
	// because is a 4-narrow search
	if ( x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 ) 
		return false;

	int i;
	for (i=0;i<depth;i++){
		color1 = mx[x1][y1][i]; 
		color2 = mx[x2][y2][i];
		diff = int(color1 - color2);
		square = diff * diff;
		sum = sum + square;

	}

	result = sqrt(sum);
	return (result < sim_factor);
}

void Image::set_plain ( bool plain )
{
	if ( isplain() && ! plain )
		type += 3;
	else if ( ! isplain() && plain )
		type -= 3;
}

int Image::get_height ()
{
	return height;
}

int Image::get_width ()
{
	return width;
}

int Image::get_depth ()
{
	return depth;
}

int Image::get_maxval ()
{ 
	return maxval;
}

void Image::set_color (int i, int j , sample* color)
{
	mx[i][j] = color;
}

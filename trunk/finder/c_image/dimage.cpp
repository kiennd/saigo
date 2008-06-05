

 #include <image.hpp>

#include <iostream>
using namespace std;

void DImage::move (int x,int y)
{
	this->x = x;
	this->y = y;
}

void DImage::draw_line (int v,int dir,sample* color)
{
	int init,end;

	if ( dir ) {
		init = v <= x ? v : x;
		end = v > x ? v : x;

		if ( init < 0 )
			init = 0;

		if ( y >= 0 && y < width ) {
			for (; init < height && init <= end ; init++ )
				mx[init][y] = color;
		}
	} else {
		init = v <= y ? v : y;
		end = v > y ? v : y;

		if ( init < 0 )
			init = 0;
		
		if (x >= 0 && x < height ) {
			for (; init < width && init <= end ; init++ )
				mx[x][init] = color;
		}

	}
}

void DImage::draw_rect (int x1,int y1,int x2,int y2,sample *color)
{
	move(x1,y1);
	draw_line (y2,0,color);
	
	move(x1,y2);
	draw_line (x2,1,color);

	move(x2,y2);
	draw_line (y1,0,color);
	
	move(x2,y1);
	draw_line (x1,1,color);
}

	

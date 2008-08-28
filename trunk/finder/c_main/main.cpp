 #include <image.hpp>
 #include <bbox.hpp>
 #include <findvar.hpp>
 #include <print.hpp>

#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include <cv.h>
#include <highgui.h>

using namespace std;

int main ( int argc , char **argv )
{	
	char *input_file = NULL, *output_file = "output_image.ppm";
	int deltavar = 10,deltah = 2,simpx = 10,range_size = 25;

	do {
		char opt = getopt(argc,argv,"i:o:v:l:s:hr:");

		if ( opt == -1 ) 
			break;

		switch (opt) {
			case 'i': input_file = optarg; 	break;
			case 'o': output_file = optarg;	break;
			case 'v': deltavar = atoi(optarg); break;
			case 'l': deltah = atoi(optarg); break;
			case 's': simpx = atoi(optarg); break;
			case 'r': range_size = atoi(optarg); break;
			case 'h':
			default:
				print::help(argv[0]);
				exit(0);
		}
	} while (1);
		

	// File Testing Section
	{
		ifstream input_test (input_file);
			
		if ( ! input_test.is_open() ) 
			print::error (argv[0],"Input not given or not exists.");
	}

	
	DImage input(input_file);
	sample color[3] = {255,0,0};


	vector<Range> *r = findvar::get_ranges(&input,deltavar,simpx,range_size);
	vector<Rect> *rects = bbox::get(&input,r,deltah);

	cout << "Found " << rects->size() << " Text Regions." <<  endl;

	vector<Rect>::iterator it;
	for ( it = rects->begin() ; it != rects->end() ; it++ ) 
		input.draw_rect (it->top-1,it->left-1,it->bottom+1,it->right+1,color);
	
	input.save(output_file);

	// teste da opencv	
	IplImage* img=cvLoadImage(output_file);
	if(!img){
    	printf("Could not load image file: %s\n",output_file);
	    exit(0);
	}

	cvNamedWindow("nham", CV_WINDOW_AUTOSIZE); 
    cvMoveWindow("nham", 100, 100);
	cvShowImage("nham",img);
	cvWaitKey(0);
	cvReleaseImage(&img );
	return 0;
}


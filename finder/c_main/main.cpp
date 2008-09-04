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
	char *inputF = NULL, *outputF = "output_image.ppm";
	int deltavar = 10,deltah = 2,simpx = 10,range_size = 25;

	do {
		char opt = getopt(argc,argv,"i:o:v:l:s:hr:");

		if ( opt == -1 ) 
			break;

		switch (opt) {
			case 'i': inputF = optarg; 	break;
			case 'o': outputF = optarg;	break;
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
	//{
	//	ifstream input_test (input_file);
	//		
	//	if ( ! input_test.is_open() ) 
	//		print::error (argv[0],"Input not given or not exists.");
	//}

	
	//DImage input(input_file);
	//sample color[3] = {255,0,0};

	if (inputF == NULL)
		print::error (argv[0],"Arquivo de entrada não fornecido.");
		
	
	IplImage* input = cvLoadImage(inputF);
	if (!input) {
		print::error (argv[0],"Arquivo de entrada não existe.");
	}
	string input_file = inputF,output_file = outputF;
	

	vector<Range> *r = findvar::get_ranges(input,deltavar,simpx,range_size);
	vector<Rect> *rects = bbox::get(input,r,deltah);

	cout << "Found " << rects->size() << " Text Regions." <<  endl;

	vector<Rect>::iterator it;
	for ( it = rects->begin() ; it != rects->end() ; it++ ) 
		cvRectangle(input, cvPoint(it->left,it->top), cvPoint(it->right,it->bottom), cvScalar(0,0,255), 1);
		//input.draw_rect (it->top-1,it->left-1,it->bottom+1,it->right+1,color);
	
	if(!cvSaveImage(output_file.c_str(),input)) 
		print::error(argv[0],"Could not save: "+output_file+ ".");

	cvNamedWindow("nham", CV_WINDOW_AUTOSIZE); 
    cvMoveWindow("nham", 100, 100);
	cvShowImage("nham",input);
	cvWaitKey(0);
	cvReleaseImage(&input);
	return 0;
}

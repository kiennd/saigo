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


void execute (char *inputF,char *outputF,int v,int l,int s,int rs) {

	IplImage* input = cvLoadImage(inputF);
	if (!input) {
		print::error ("Erro:","Arquivo de entrada não existe.");
	}	

	vector<Range> *r = findvar::get_ranges(input,v,s,rs);
	vector<Rect> *rects = bbox::get(input,r,l);

	cout << "Encontrou " << rects->size() << " Regioes de Texto." <<  endl;
	
	vector<Rect>::iterator it;
	for ( it = rects->begin() ; it != rects->end() ; it++ ) 
		cvRectangle(input, cvPoint(it->left,it->top), cvPoint(it->right,it->bottom), cvScalar(0,0,255), 1);

	if(!cvSaveImage(outputF,input)) 
		print::error("Erro:","Não foi possivel salvar em "+string(outputF)+ ".");

}

void display (vector<IplImage*> *images) {

	int i = 0;
	cvNamedWindow("nham", CV_WINDOW_AUTOSIZE); 
    cvMoveWindow("nham", 100, 100);

	if (images->size() <= 0 )
		return;
	else {
		cvShowImage("nham",images->at(0));
	}

	char key;
	do {
		key = cvWaitKey(0);
		if ( key == 'S' ) {
			if ( i+1 < images->size() ) {
				i += 1;
			}
		} else if ( key == 'Q' ) {	
			if ( i-1 >= 0 ) {
				i -= 1;
			}
		} else {
			break;
		}
		cvShowImage("nham",images->at(i));
	} while(1);
}

int main ( int argc , char **argv )
{	
	char *inputF = NULL, *outputF = "output_image.ppm";
	int v = 10,l = 2,s = 10,r = 25;

	do {
		char opt = getopt(argc,argv,"i:o:v:l:s:hr:");

		if ( opt == -1 ) 
			break;

		switch (opt) {
			case 'i': inputF = optarg; 	break;
			case 'o': outputF = optarg;	break;
			case 'v': v = atoi(optarg); break;
			case 'l': l = atoi(optarg); break;
			case 's': s = atoi(optarg); break;
			case 'r': r = atoi(optarg); break;
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

	/*
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
	*/

	execute(inputF,outputF,v,l,s,r);
	
	vector<IplImage*> *images = new vector<IplImage*>[2];
	images->push_back(cvLoadImage(inputF));
	images->push_back(cvLoadImage(outputF));
	
	display(images);
		
	//cvReleaseImage(&input);
	
	return 0;
}

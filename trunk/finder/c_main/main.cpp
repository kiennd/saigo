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

void salvaRegioes (IplImage* input, vector<Rect> *rects, char* outputFileName) {
	IplImage* imgTeste;
	CvRect retInteresse;
	char caminhoArquivo[255];
	int i = 1;
		vector<Rect>::iterator it;
		for ( it = rects->begin() ; it != rects->end() ; it++ ) {
		if ((it->right - it->left > 0) && (it->bottom-it->top > 0)) {
		retInteresse = cvRect(it->left,it->top,it->right-it->left,it->bottom-it->top);
		imgTeste = cvCreateImage(cvSize(retInteresse.width,retInteresse.height),input->depth,input->nChannels);
		cvSetImageROI( input, retInteresse );
    cvCopy( input, imgTeste, NULL );
    
    sprintf(caminhoArquivo,"%sregion%d.jpg",outputFileName,i);
    cvSaveImage(caminhoArquivo,imgTeste);
    i++;
    cvResetImageROI(input);
    }
    //cout << "dimensoes ret: " << it->right - it->left << " " << it->bottom-it->top << "\n" ;
  }

}

void execute (char *inputF,char *outputF,int v,int l,int s,int rs, bool salvarRetangulos) {

	IplImage* input = cvLoadImage(inputF);
	if (!input) {
		print::error ("Erro:","Arquivo de entrada não existe.");
	}	

	vector<Range> *r = findvar::get_ranges(input,v,s,rs);
	vector<Rect> *rects = bbox::get(input,r,l);

	cout << "Encontrou " << rects->size() << " Regioes de Texto." <<  endl;
  if (salvarRetangulos) {
   	salvaRegioes(input, rects, outputF);
  }
	vector<Rect>::iterator it;
	for ( it = rects->begin() ; it != rects->end() ; it++ ) {
    cvRectangle(input, cvPoint(it->left,it->top), cvPoint(it->right,it->bottom), cvScalar(0,0,255), 1);
  }

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
	int v = 12,l = 5,s = 60,r = 10;
  bool salvarRetangulos = false;
	do {
		char opt = getopt(argc,argv,"i:o:v:l:s:hgr:");

		if ( opt == -1 ) 
			break;

		switch (opt) {
			case 'i': inputF = optarg; 	break;
			case 'o': outputF = optarg;	break;
			case 'v': v = atoi(optarg); break;
			case 'l': l = atoi(optarg); break;
			case 's': s = atoi(optarg); break;
			case 'r': r = atoi(optarg); break;
			case 'g': salvarRetangulos = true; break;
			case 'h':
			default:
				print::help(argv[0]);
				exit(0);
		}
	} while (1);

	if ( inputF != NULL ) {
		execute(inputF,outputF,v,l,s,r, salvarRetangulos);
	
		vector<IplImage*> *images = new vector<IplImage*>[2];
		images->push_back(cvLoadImage(inputF));
		images->push_back(cvLoadImage(outputF));
	
		display(images);
	}
			
	return 0;
}

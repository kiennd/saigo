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

// imgAux
IplImage* getRectImage (IplImage *input,Rect& r,int b) {
	IplImage *region;

	CvRect retInteresse = cvRect(r.left,r.top-b,(r.right-r.left)+b,(r.bottom-r.top)+b);
	region = cvCreateImage(cvSize(retInteresse.width,retInteresse.height),input->depth,input->nChannels);
	cvSetImageROI( input, retInteresse );
    cvCopy( input, region, NULL );
	cvResetImageROI(input);

	return region;
}

int getThreshold (CvScalar mediaCorInteresse) {

	int limiarBinarizacao;	
	limiarBinarizacao = (int) mediaCorInteresse.val[0];
	if (mediaCorInteresse.val[1] > limiarBinarizacao)
	  limiarBinarizacao = (int) mediaCorInteresse.val[1];
	if (mediaCorInteresse.val[2] > limiarBinarizacao)
	  limiarBinarizacao = (int) mediaCorInteresse.val[2];	

	return limiarBinarizacao;
}

IplImage* binarize (IplImage *input,int limiarBinarizacao) {
	int x,y;
	CvScalar s;
	for (x=0;x<input->height;x++) for (y=0;y<input->width;y++) {
		s = cvGet2D(input,x,y);
		if ((s.val[0] > limiarBinarizacao) || (s.val[1] > limiarBinarizacao) || (s.val[2] > limiarBinarizacao)) {
			s.val[0] = s.val[1] = s.val[2] = 255;
		} else {
			s.val[0] = s.val[1] = s.val[2] = 0;
		}
		cvSet2D(input,x,y,s);
	}
	return input;
}

// space
bool isSpaceColumn (IplImage *input,int col) {
	bool ehEspaco = true;
	CvScalar pixel;
	int y;
	for (y=0;y<input->height;y++) {
      pixel = cvGet2D(input,y,col);
      if (pixel.val[0] != 0)
        ehEspaco = false;      
    }
	return ehEspaco;
}

double media (vector<Range> *espacos) {
	
	int i;
	double media = 0;
	Range r;
	for (i = 0; i < espacos->size() ; i++ ) {
		r = espacos->at(i);
		media =  (r.right-r.left) * (1.0/(i+1)) + media * (((double)i)/(i+1));
	}
	return media;
}

vector<Range>* getEspacoReal (vector<Range>* todosEspacos, double media) {

	int i;
	Range r;
	vector<Range> *espacos = new vector<Range>();
	for (i=0; i< todosEspacos->size() ; i++ ){
		r = todosEspacos->at(i);
		if ( (r.right-r.left) > media )
			espacos->push_back(r);
	}

	return espacos;
}

vector<Rect> *getWords (IplImage *input,vector<Range>*espacos) {

	int i;
	Range r;
	Rect rect;
	vector<Rect>* words = new vector<Rect>();

	int left=0;
	for (i=0; i< espacos->size() ; i++ ){
		r = espacos->at(i);
		rect.top = 0;
		rect.bottom = input->height;
		rect.left = left;
		rect.right = r.left;
		words->push_back(rect);

		left = r.right;
	}
	rect.top = 0;
	rect.bottom = input->height;
	rect.left = left;
	rect.right = input->width;
	words->push_back(rect);

	return words;
}


vector<Range>* findSpaces (IplImage* input) {

	int meioAltura = input->height / 2;
	int x;
	CvScalar pixel;
	vector<Range> *espacos = new vector<Range>();
	Range r;
	r.left = r.right = 0;

	for (x=0;x<input->width;x++) {
	    pixel = cvGet2D(input,meioAltura,x);
		if (pixel.val[0] == 0) {
			if ( isSpaceColumn (input,x) )
				if ( r.left == 0 )
      				r.left = x;
			    else
      				r.right = x;
      	
		} else {
			if ( r.right == 0 )
				r.right = r.left;

			if ( r.left != 0 ) {
				//cout << "pixel de espaço: " << r.left << "," << r.right << "\n";
				espacos->push_back(r);
	  	    	r.left = r.right = 0;      
  		    }
   		}	   
   
  	}
	return espacos;
}

void salvaPalavras (IplImage* input, vector<Rect> *rects, char* outputFileName, int b) {
	IplImage* imgTeste;
	char caminhoArquivo[255];
	char diretorio[255];
	char comando[255];
	int i = 1;

	sprintf(diretorio,"%s_dir",outputFileName);
	sprintf(comando,"bash -c '[[ -d %s ]] || mkdir %s'",diretorio,diretorio);	
	system(comando);

	int j;
	Rect r;
	for ( j = 0 ; j < rects->size() ; j++ ) {
	  r = rects->at(j);  
	
	  if ((r.right - r.left > 0) && (r.bottom-r.top > 0)) {
	              
		imgTeste = getRectImage (input,r,b);    
		sprintf(caminhoArquivo,"%s/word%d.bmp",diretorio,i);
        cvSaveImage(caminhoArquivo,imgTeste);
        i++;
      }
	}
}




void salvaRegioes (IplImage* input, vector<Rect> *rects, char* outputFileName, CvScalar mediaCorInteresse, int b) {
	IplImage* imgTeste;
	char caminhoArquivo[255];
	char diretorio[255];
	char comando[255];
	int i = 1;

	sprintf(diretorio,"%s_dir",outputFileName);
	sprintf(comando,"bash -c '[[ -d %s ]] || mkdir %s'",diretorio,diretorio);	
	system(comando);

	int limiarBinarizacao = getThreshold(mediaCorInteresse);	
  	cout << "Limiar binarização calculado: " << limiarBinarizacao << "\n";
	 
	int j;
	Rect r;
	for ( j = 0 ; j < rects->size() ; j++ ) {
	  r = rects->at(j);  
	
	  if ((r.right - r.left > 0) && (r.bottom-r.top > 0)) {
	              
		imgTeste = getRectImage (input,r,b);
		imgTeste = binarize(imgTeste,limiarBinarizacao);
            
		sprintf(caminhoArquivo,"%s/region%d.bmp",diretorio,i);
		vector<Range> *espacos = findSpaces(imgTeste);
		salvaPalavras(imgTeste, getWords(imgTeste,getEspacoReal(espacos,media(espacos))),caminhoArquivo,0);
        cvSaveImage(caminhoArquivo,imgTeste);
        i++;
      }
	}
}

void execute (char *inputF,char *outputF,int v,int l,int s,int rs, bool salvarRetangulos, int b) {

	IplImage* input = cvLoadImage(inputF);
	if (!input) {
		print::error ("Erro:","Arquivo de entrada não existe.");
	}	
	CvScalar mediaCorInteresse;
	vector<Range> *r = findvar::get_ranges(input,v,s,rs,&mediaCorInteresse);
	vector<Rect> *rects = bbox::get(input,r,l);

	cout << "Encontrou " << rects->size() << " Regioes de Texto." <<  endl;
  	if (salvarRetangulos) 
   		salvaRegioes(input, rects, outputF, mediaCorInteresse, b);
	
	vector<Rect>::iterator it;
	for ( it = rects->begin() ; it != rects->end() ; it++ ) {
		cvRectangle(input, cvPoint(it->left,it->top), cvPoint(it->right,it->bottom), cvScalar(0,0,255), 1);
	}

	if(!cvSaveImage(outputF,input)) 
		print::error("Erro:","Não foi possivel salvar em "+string(outputF)+ ".");

}

void display (vector<IplImage*> *images) {

	int i = 0;
	cvNamedWindow("window", CV_WINDOW_AUTOSIZE); 
    cvMoveWindow("window", 100, 100);

	if (images->size() <= 0 )
		return;
	else {
		cvShowImage("window",images->at(0));
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
		cvShowImage("window",images->at(i));
	} while(1);
}

int main ( int argc , char **argv )
{	
	char *inputF = NULL, *outputF = (char *) "output_image.ppm";
	int v = 15,l = 6,s = 100,r = 8,b=0;
	bool salvarRetangulos = false;
	bool mostrarResultado = false;
	do {

		char opt = getopt(argc,argv,"i:o:v:l:s:hgwr:b:");


		if ( opt == -1 ) 
			break;

		switch (opt) {
			case 'i': inputF = optarg; 	break;
			case 'o': outputF = optarg;	break;
			case 'v': v = atoi(optarg); break;
			case 'l': l = atoi(optarg); break;
			case 's': s = atoi(optarg); break;
			case 'r': r = atoi(optarg); break;
			case 'b': b = atoi(optarg); break;
			case 'g': salvarRetangulos = true; break;
			case 'w': mostrarResultado = true; break;
			case 'h':
			default:
				print::help(argv[0]);
				exit(0);
		}
	} while (1);

	if ( inputF != NULL ) {
		execute(inputF,outputF,v,l,s,r, salvarRetangulos, b);
	
		vector<IplImage*> *images = new vector<IplImage*>[2];
		images->push_back(cvLoadImage(inputF));
		images->push_back(cvLoadImage(outputF));
	
		if ( mostrarResultado )
			display(images);
	}
			
	return 0;
}

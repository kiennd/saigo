 #include <image.hpp>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

int GImage::gnuplot_hist_data ( string dat_file )
{
	ofstream fs (dat_file.c_str());

	int *hist = histogram();
	// 'file_name' will be formated like:
    // <grayscale> <num_of_pixels>
    int i,max = 0;
    for ( i = 0; i < (maxval + 1); i++) {
        if ( hist[i] )
			fs << i << ' ' << hist[i] << endl;
        if ( hist[i] > max )
            max = hist[i];
    }
	fs.close();
	return max;
}


void GImage::gnuplot_histogram ( string jpg_file ) 
{	
	FILE *gp;
    string dat_file = "tmpfile.123" ;
	int max = gnuplot_hist_data (dat_file);

    gp = popen("gnuplot","w");

    // Sends a command to gnuplot via pipe
    fprintf(gp, "set output '%s'; set terminal jpeg; set style \
				fill solid ; set boxwidth 0.1; plot [0:255] [0:%d] \
				'%s' with boxes\n",jpg_file.c_str(),max,dat_file.c_str());

    fflush(gp);
    pclose(gp);
}


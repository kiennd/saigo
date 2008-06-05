#ifndef __IMAGE_HPP__

#include <string>
using namespace std;

typedef unsigned char sample;

class Image {
	protected:
		int type , height , width , depth;
		sample maxval;
		sample ***mx;

	public:
		Image (string);
		Image (Image&);

		int get_height();
		int get_width();
		int get_depth();
		int get_maxval();
		void set_color (int,int,sample*);
		
		bool isplain();
		bool isppm();
		bool issimilar(int,int,int,int,double);
		void set_plain (bool);

		void save (string);

		int *histogram (int=0);
		sample higher_val ();
		double rmse(Image*);
		double psnr(Image*);

		Image *dithering();
		Image *negative ();
		void rotate (int);

		Image *non_linear_transform ( double (*func)(sample) );
		Image *linear_transform (double=0.75,double=2,double=0.25);

		static const int ROTATE_RIGHT = 1;
		static const int ROTATE_LEFT = 0;

};

class GImage : public Image {
    protected:
        int gnuplot_hist_data( string dat_file );

    public:
        void gnuplot_histogram (string);
};

class DImage : public Image {
	private:
		int x,y;
	public:
		DImage(string s) : Image(s) { return;}
		void move (int,int);
		void draw_line (int,int,sample*);

		void draw_rect (int,int,int,int,sample*);

};

#endif
#define __IMAGE_HPP__

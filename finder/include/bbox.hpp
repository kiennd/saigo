#ifndef __BBOX_HPP__

#include <cv.h>
#include <vector>
#include <findvar.hpp>

using namespace std;

struct Rect {
	int left,right,top,bottom;
	int count;
	int matched;
};


namespace bbox {
	vector<Rect>* get (IplImage*,vector<Range>*,int);
}; 

#endif
#define __BBOX_HPP__

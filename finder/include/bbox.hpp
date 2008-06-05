#ifndef __BBOX_HPP__

#include <vector>
#include <findvar.hpp>

struct Rect {
	int left,right,top,bottom;
	int count;
	int matched;
};


namespace bbox {
	vector<Rect>* get (Image*,vector<Range>*,int);
}; 

#endif
#define __BBOX_HPP__

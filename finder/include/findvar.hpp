#ifndef __FINDVAR_HPP__

#include <vector>
#include <image.hpp>

struct Range {
	int left,right;
};

namespace findvar {
	vector<Range>* get_ranges(Image*,int,int,int);
	int firstpx_index (Image*,int,int,int);
	int lastpx_index (Image*,int,int,int&,int);
};

#endif
#define __FINDVAR_HPP__

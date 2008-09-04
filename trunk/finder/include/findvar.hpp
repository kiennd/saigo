#ifndef __FINDVAR_HPP__

#include <vector>
#include <imgAux.hpp>

using namespace std;

struct Range {
	int left,right;
};

namespace findvar {
	int firstpx_index (IplImage*,int,int,int);
	int lastpx_index (IplImage*,int,int,int&,int);
	vector<Range>* get_ranges(IplImage*,int,int,int);
};

#endif
#define __FINDVAR_HPP__

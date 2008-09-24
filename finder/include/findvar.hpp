#ifndef __FINDVAR_HPP__

#include <vector>
#include <imgAux.hpp>

using namespace std;

struct Range {
	int left,right;
	CvScalar corInteresse;
};

namespace findvar {
	int firstpx_index (IplImage*,int,int,int);
	int lastpx_index (IplImage*,int,int,int&,int, CvScalar*);
	vector<Range>* get_ranges(IplImage*,int,int,int, CvScalar*);
};

#endif
#define __FINDVAR_HPP__


#include <vector>
 #include <findvar.hpp>
 #include <bbox.hpp>

vector<Rect>* bbox::get (Image*img,vector<Range>*ranges,int hpx)
{
	int i,j,u;
	vector<int> matched_rect;
	vector<Rect> open,*closed;
	Rect r;

	closed = new vector<Rect>;

	for ( i = 0 ; i < img->get_height(); i++ ) {
		for ( j = 0 ; j < ranges[i].size() ; j++ ) {
		
			matched_rect.clear();	
			for ( u = 0 ; u < open.size() ; u++ ) {

				if ( ! ( open[u].left > ranges[i][j].right || open[u].right < ranges[i][j].left ) ) {
					matched_rect.push_back(u);
				}
			}

		
			r.left = ranges[i][j].left;
			r.right = ranges[i][j].right;
			r.top = r.bottom = i;
			r.count = hpx;
			r.matched = 1;
			
			int size = matched_rect.size();
			for ( u = size-1 ; u >= 0 ; u-- ) {

				if ( open[matched_rect[u]].left < r.left )
					r.left = open[matched_rect[u]].left;

				if ( open[matched_rect[u]].right > r.right )
					r.right = open[matched_rect[u]].right;

				if ( open[matched_rect[u]].top < r.top )
					r.top = open[matched_rect[u]].top;


				r.bottom = i;
				open.erase(open.begin()+matched_rect[u]);
			}
			open.push_back(r);	
		}

		for ( u = open.size()-1 ; u >= 0 ; u-- ) {
			if ( ! open[u].matched ) {
				open[u].count -= 1;
			} else {
				open[u].count = hpx;
				open[u].matched = 0;
			}

			if ( ! open[u].count ){
				(*closed).push_back(open[u]);
				open.erase(open.begin()+u);
			}
		} 
	}

	return closed;
}

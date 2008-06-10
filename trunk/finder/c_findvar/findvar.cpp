
#include <vector>
 #include <image.hpp>

 #include <findvar.hpp>

int findvar::firstpx_index (Image *img,int x,int y,int simpx)
{
	while ( y < img->get_width() && img->issimilar(x,y-1,x,y,simpx) )
		y++;

	return y;
}

int findvar::lastpx_index (Image *img,int x,int y,int& delta,int simpx)
{
	int eq = 0,lastpx;
	int region_count = 1;
	int primy = y;
	bool pegaintervalo=true;
	do {

		// se tiver ponto perdido no ultimo pixel pode dar merda.

		// Primeiro loop inicia lastpx
		if ( img->issimilar(x,y-1,x,y,simpx) )
			eq++;
		else {
			eq = 0;
			//só pega o intervalo se as cores são similares com a de primy
			if (pegaintervalo) {
			    lastpx = y-1;
				if (lastpx > y) 
					delta = (delta*region_count + eq) / (++region_count);
			}			
			if (img->issimilar(x,primy,x,y,simpx))
			  pegaintervalo = true;
			else {
				if (pegaintervalo)			
				  pegaintervalo = false;  
				//else
				//retorna se a nova cor é diferente da cor de primy e intervalo anterior não interessa 
				//return lastpx;
			}
		}
		
		y++;
	} while ( y < img->get_width() && eq < delta );

	return lastpx;
}

#include <iostream>
using namespace std;

vector<Range>* findvar::get_ranges(Image *img,int delta_var,int simpx,int range_size)
{
	vector<Range>* ranges = new vector<Range>[img->get_height()];

	int i;
	Range r;
	for (i = 0; i < img->get_height() ; i++) {
		r.left = 1;
		while (r.left < img->get_width()) {

			r.left = firstpx_index (img,i,r.left,simpx);

			if ( r.left < img->get_width() ) {
				r.right = lastpx_index (img,i,r.left,delta_var,simpx);
		
				if ( r.right - r.left > range_size)	
					ranges[i].push_back(r);

				// Para comparar somente com pixels ainda nao vistos 
				r.left = r.right + 2;
			}
		}
		cout << delta_var << " " << endl;
			
	}
	return ranges;
}
	
	

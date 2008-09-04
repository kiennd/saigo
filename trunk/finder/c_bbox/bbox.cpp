
#include <cv.h>
#include <vector>
 #include <findvar.hpp>
 #include <bbox.hpp>

vector<Rect>* bbox::get (IplImage *img,vector<Range>*ranges,int hpx)
{
	int i,j,u;
	vector<int> matched_rect;
	vector<Rect> open,*closed;
	Rect r;

	closed = new vector<Rect>;

	// Cada linha tem em ranges, os intervalos que contem texto encontrados
	// ranges[0] : todos intervalos da linha 0
	// ranges[1] : todos intervalos da linha 1, assim por diante
	for ( i = 0 ; i < img->height; i++ ) {
		for ( j = 0 ; j < ranges[i].size() ; j++ ) {
		
			// Verifica se o intervalo atual encaixa com algum retangulo que esta sendo construindo
			// e armazena os retangulos que encaixaram
			// 
			// ...Na verdade armazena o indice do retangulo em open
			matched_rect.clear();	
			for ( u = 0 ; u < open.size() ; u++ ) {

				if ( ! ( open[u].left > ranges[i][j].right || open[u].right < ranges[i][j].left ) ) {
					matched_rect.push_back(u);
				}
			}

		
			// Retangulo inicial criado para o intervalo
			r.left = ranges[i][j].left;
			r.right = ranges[i][j].right;
			r.top = r.bottom = i;
			r.count = hpx;
			r.matched = 1;
			
			
			// Todos os retangulos que casaram de alguma forma com o intervalo
			// Vao modificar as dimensoes deste retangulo, depois serao jogados fora
			// dando lugar a este novo retangulo.
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

		// Zera o contador que o retangulo casou na ultima passada
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

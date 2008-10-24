
all: relatorio.pdf clean

relatorio.pdf: relatorio.tex imagens referencia.bbl
	pdflatex $<
	pdflatex $<

relatorio.tex: relatorio.t2t
	../txt2tags-2.3/txt2tags -t tex -o relatorio.tex $<

referencia.bbl: referencia.bib
	pdflatex relatorio.tex
	bibtex relatorio

.PHONY: clean distclean

clean: 
	@rm -f *.log *.out *.aux *.blg *.bbl

distclean: clean
	@rm -f relatorio.pdf relatorio.tex
	

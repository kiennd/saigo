
all: relatorio.pdf clean

relatorio.pdf: relatorio.tex imagens
	pdflatex $<

relatorio.tex: relatorio.t2t
	../txt2tags -t tex -o relatorio.tex $<
	
.PHONY: clean distclean

clean: 
	@rm -f *.log *.out *.aux

distclean: clean
	@rm -f relatorio.pdf relatorio.tex
	

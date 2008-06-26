
all: relatorio.pdf clean

relatorio.pdf: relatorio.tex imagensRelatorio22042008
	pdflatex $<

relatorio.tex: Relatorio220408.t2t
	../txt2tags-2.3/txt2tags -t tex -o relatorio.tex $<
	
.PHONY: clean distclean

clean: 
	@rm -f *.log *.out *.aux

distclean: clean
	@rm -f relatorio.pdf relatorio.tex
	

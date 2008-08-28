DEPTH = .
include $(DEPTH)/build/default.mk

MODULES = main.a image.a bbox.a findvar.a print.a
PROGRAM = finder.bin
EXTRA = finder

include $(DEPTH)/build/toplevel.mk

.PHONY: $(EXTRA)

$(EXTRA):
	@$(RM) ./$@
	@echo "#!/bin/bash" >> $@
	@echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:$(PWD)/opencv/lib" >> $@
	@echo "$(PWD)/$(PROGRAM) \$$@" >> $@
	@chmod a+x $@

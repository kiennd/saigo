# Generic Makefile for Library Compilation
# Laerte Alves de Almeida Junior
# ljchrono@gmail.com
# 23/11/06

# Configuration Parameters
# EXTENSION
# LIBNAME


include $(DEPTH)/build/default.mk

OBJ = $(patsubst %.$(EXTENSION),%.o,$(wildcard *.$(EXTENSION)))
INCLUDE_DEP = $(shell bash $(DEPTH)/build/idep.sh -e $(EXTENSION) *.$(EXTENSION) )


all: $(LIBNAME)

$(LIBNAME) : $(OBJ)
	$(AR) $@ $(OBJ)
	
%.o : %.$(EXTENSION) $(INCLUDE_DEP)
	$(CC) $(CFLAGS) -c $< $(IFLAGS)

.PHONY: clean distclean

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(LIBNAME)

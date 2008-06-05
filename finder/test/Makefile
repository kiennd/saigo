DEPTH = ..
include $(DEPTH)/build/default.mk

TRASH = $(patsubst %.cpp,%,$(wildcard *.cpp))

all: stl sanity

sanity : sanity.cpp $(DEPTH)/image.a
	$(CC) $(CFLAGS) -o $@ $^ $(IFLAGS)

%:	%.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(IFLAGS)

%.a: 
	make -C $(DEPTH) $(notdir $@)

.PHONY: clean distclean

clean: 
	$(RM) $(TRASH)

distclean: clean
		

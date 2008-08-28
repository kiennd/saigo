CC = LD_LIBRARY_PATH=$(DEPTH)/opencv/lib g++
CFLAGS = -g
IFLAGS = -I$(DEPTH)/include -I$(DEPTH)/opencv/include/opencv
LFLAGS = -L$(DEPTH)/opencv/lib -lm -lcv -lhighgui -lcvaux
RM = /bin/rm -f
AR = ar rcs
SUBDIRS = $(wildcard c_*)
TRASH = #./*.pgm ./*.ppm ./*.jpg ./*.dat

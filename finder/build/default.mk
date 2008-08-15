CC = g++
CFLAGS = -g
IFLAGS = -I$(DEPTH)/include -I$(PWD)/opencv/include/opencv
LFLAGS = -L$(PWD)/opencv/lib -lm -lcv -lhighgui -lcvaux
RM = /bin/rm -f
AR = ar rcs
SUBDIRS = $(wildcard c_*)
TRASH = #./*.pgm ./*.ppm ./*.jpg ./*.dat

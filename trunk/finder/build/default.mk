CC = g++
CFLAGS = -g
IFLAGS = -I$(DEPTH)/include
LFLAGS = -lm
RM = /bin/rm -f
AR = ar rcs
SUBDIRS = $(wildcard c_*)
TRASH = #./*.pgm ./*.ppm ./*.jpg ./*.dat

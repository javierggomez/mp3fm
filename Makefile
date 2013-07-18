# Makefile for mp3fm.
# (C) 2013 Javier Garcia Gomez

CXX=g++
CXXFLAGS=-Wall -Wno-multichar -std=c++0x
CC=g++
CFLAGS=-Wall -Wno-multichar -std=c++0x
MATHFLAGS=-lm
MADFLAGS=-lmad
THREADFLAGS=-lpthread

mp3fm: mp3fm.o mp32wav.o bstdfile.o libpifm.o cscopedlock.o Makefile
	$(CXX) $(CXXFLAGS) -o mp3fm mp3fm.o mp32wav.o bstdfile.o libpifm.o cscopedlock.o $(MATHFLAGS) $(MADFLAGS) $(THREADFLAGS)

clean:
	-rm -rf *.o *~

all: tempclient 

#client/player

#server

#tempclient
tempclient: tempclient.c asciiesc.h asciiesc.o
	cc -o tempclient tempclient.c asciiesc.o

#asciiesc
asciiesc.o: asciiesc.c asciiesc.h
	cc -c -o asciiesc.o asciiesc.c 
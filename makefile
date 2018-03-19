all: client.o server.o

client.o:	client.c	client.h
	gcc	-o	client	client.c	client.h

server.o:	server.c	server.h
	gcc	-o	server	server.c	server.h

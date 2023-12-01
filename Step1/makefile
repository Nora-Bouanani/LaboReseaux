
# cphex\makefile

LIBS=
all:	admin	LibSerBL.o


LibSerBL.o:	LibSerBL.c	LibSerBL.h	data.h	
	echo "compilation de LibSerBL"
	gcc -c LibSerBL.c

admin:	data.h	admin.c	LibSerBL.o			
	echo "Compilation de admin"
	gcc -o admin	admin.c	LibSerBL.o 


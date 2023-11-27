# cphex\makefile

LIBS=
all: admin cli ser udplib.o LibSerBL.o
LibSerBL.o: LibSerBL.c LibSerBL.h data.h
	echo "compilation de LibSerBL"
	cc -c LibSerBL.c
admin: data.h admin.c LibSerBL.o
	echo "Compilation de admin"
	cc -o admin admin.c LibSerBL.o
udplib.o: ../udplib/udplib.h ../udplib/udplib.c
	echo "Compilation de udplib.o"
	cc -c ../udplib/udplib.c
cli: cli.c requeteBL.h data.h udplib.o
	echo "Compilation de client"
	cc -o cli cli.c udplib.o $(LIBS)
ser: ser.c requeteBL.h data.h udplib.o LibSerBL.o
	echo "Compilation de serveur"
	cc -o ser ser.c udplib.o LibSerBL.o $(LIBS)

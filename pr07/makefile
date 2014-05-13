all: sender erzeuger delete

sender: pv.o
	gcc pv.o sender.c -o sender

erzeuger: pv.o
	gcc pv.o erzeuger.c -o erzeuger

delete: 
	gcc delete.c -o delete	

pv.o: 
	gcc -c pv.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include "sm.h"

int sem_anfordid;

int main(int argc,char* argv[])
{
	int anzahl_ressourcen,freie_ressourcen;
	int i;

	/* Uebergebene Argumente pruefen */
	if(argc!=2){
		fprintf(stderr,"usage: %s <Anzahl Ressourcen>\n",argv[0]);
		exit(-1);
	}
	
	/* Übergebene Anzahl von Resourcen in integer wandeln */
	int decrement = atoi(argv[1]);
	printf("Konsumiere %d Ressourcen\n", decrement);

	/* Verbinden des Semaphors */
	sem_anfordid = sem_connect(SEM_READKEY);

	/* Ressourcen anfordern */
	pv(sem_anfordid, -decrement);

	/* Anzahl der noch verfügbaren Ressourcen abfragen */
	int ressourcen = sem_get(sem_anfordid);

   /* Anzahl der freigegebene und der insgesamt freien Ressourcen ausgeben */
	printf("Jetzt sind %d Ressourcen frei\n", ressourcen);

	exit(0);
}

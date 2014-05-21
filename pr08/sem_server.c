#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include "sm.h"
#include "pv.h"

static int sem_anfordid;

int main(int argc, char *argv[])
{
	if(argc == 2){
		char clear_str[] = "clear";

		if(strcmp(clear_str, argv[1]) == 0){
			sem_anfordid = sem_connect(SEM_READKEY);
			sem_rm(sem_anfordid);
			printf("%s\n", "Semaphore entfernt.");
		}

		exit(0);
	}

	int freie_ressourcen;

	/* Anlegen des Semaphors */
	sem_anfordid = sem_create(SEM_READKEY);

	/* Setzen des Sempahors auf 1 */
	sem_set(sem_anfordid, 1);


	int anz_res_old = 0;
	/* Beginn Serverschleife */
	while(1){
		/* Abfragen wieviel Ressourcen frei sind, falls 0 Schleife verlassen */
		int anz_ressourcen = sem_get(sem_anfordid);
		if(anz_res_old == anz_ressourcen) {
			printf(".");
			fflush(stdout);
		}
		else {
			printf("\nSem-Wert(Res.-Anzahl): %d", anz_ressourcen);
			anz_res_old = anz_ressourcen;
		}
		if(anz_ressourcen == 0){
			break;
		}
		
		/* eine Sekunde warten */
		sleep(1);
	/* Ende Serverschleife */
	}
	
	/* Semaphor entfernen */
	sem_rm(sem_anfordid);

	exit(0);
}

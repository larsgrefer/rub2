#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "sm.h"
#include "pv.h"

static int shm_anfordid,shm_antwortid;
static int sem_anfordid,sem_antwortid;
static struct sembuf semaphor;


int main(int argc,char* argv[])
{
	int client,neues_wort;
	anforder_shm	*shm_anford;
	antwort_shm 	*shm_antwort;

        /* Uebergebene Argumente pruefen */
        if(argc != 3){
                fprintf(stderr, "usage: %s client_nr string\n", argv[0]);
                exit(-1);
        }
        if((client = atol(argv[1])) == 0){
                fprintf(stderr, "client_nr muss eine Zahl sein\n");
                exit(-1);
        }

	/******************************** initialisieren *********************************/

	/* Anlegen des Shared Memories fuer Anforderungen */
	if((shm_anfordid = shmget(SHM_READKEY, MAX_LAENGE, 0)) == -1){
		fprintf(stderr,"Error: Anforderungs shared memory konnte nicht angelegt werden\n");
		exit(-1);
	}

	/* Anbinden des Shared Memories fuer Anforderungen */
	if((shm_anford = shmat(shm_anfordid, NULL, 0)) == (void*)-1){
		fprintf(stderr, "Error: Anforderungs shared memory konnte nicht angebunden werden\n");
		exit(-1);
	}

	/* Anlegen des Shared Memories fuer Antworten */
	if((shm_antwortid = shmget(SHM_WRITEKEY, MAX_LAENGE, 0)) == -1){
		fprintf(stderr, "Error: Antwort shared memory konnte nicht angelegt werden\n");
		exit(-1);
	}

	/* Anbinden des Shared Memories fuer Antworten */
	if((shm_antwort = shmat(shm_antwortid, NULL, 0)) == (void*)-1){
		fprintf(stderr, "Error: Antwort shared memory konnte nicht angebunden werden\n");
		exit(-1);
	}

        /* Anlegen des Semaphors fuer Anforderungen */
        if((sem_anfordid = semget(SEM_READKEY, 0, 0)) == -1){
                fprintf(stderr, "Error: semaphore (Anforderungen) konnte nicht angelegt werden\n");
                exit(-1);
        }

        /* Anlegen des Semaphors fuer Antworten */
        if((sem_antwortid = semget(SEM_WRITEKEY, 0, 0)) == -1){
                fprintf(stderr, "Error: semaphore (Antworten) konnte nicht angelegt werden\n");
                exit(-1);
        }

	/****************************** Senden einer Anforderung ************************************/

	while(1)
	{
		neues_wort = 0;

		/* Semaphor fuer Anforderungen setzen */
		semaphor.sem_op = -1;
                semaphor.sem_flg = SEM_UNDO;

                /* Anfordern einer Ressource */
                if(semop(sem_anfordid, &semaphor, 1) == -1){
                        fprintf(stderr, "Error: semaphore (Anforderungen) konnte nicht dekrementiert werden\n");
                        exit(-1);
                }

		if(!shm_anford->ungelesen){
			strcpy(shm_anford->text, argv[2]);
			shm_anford->client_nr = client;
			shm_anford->ungelesen = 1;
			neues_wort = 1;
		}
		
		/* Semaphor fuer Anforderungen freigeben */
		semaphor.sem_op = 1;
                semaphor.sem_flg = SEM_UNDO;

                /* Freigeben einer Ressource */
                if(semop(sem_anfordid, &semaphor, 1) == -1){
                        fprintf(stderr, "Error: semaphore (Anforderungen) konnte nicht inkrementiert werden\n");
                        exit(-1);
                }
		
		if(neues_wort)
			break;
		else
			sleep(1);

	}

	/****************************** Warten auf die Antwort **********************************/

	while(client != SHM_MAXSAETZE)
	{
		/* Semaphor fuer Antworten setzen */
		semaphor.sem_op = -1;
                semaphor.sem_flg = SEM_UNDO;

                /* Anfordern einer Ressource */
                if(semop(sem_antwortid, &semaphor, 1) == -1){
                        fprintf(stderr, "Error: semaphore (Antworten) konnte nicht dekrementiert werden\n");
                        exit(-1);
                }

		if((shm_antwort->ungelesen) && (shm_antwort->client_nr == client)){

			printf("Rückmeldung: %s\n", shm_antwort->ergebnis);
			shm_antwort->ungelesen = 0;

			/* Semaphor fuer Antworten freigeben */
			semaphor.sem_op = 1;
                	semaphor.sem_flg = SEM_UNDO;

                	/* Freigeben einer Ressource */
                	if(semop(sem_antwortid, &semaphor, 1) == -1){
                        	fprintf(stderr, "Error: semaphore (Antworten) konnte nicht inkrementiert werden\n");
                        	exit(-1);
                	}

			break;
		}
		else{
		
			/* Semaphor fuer Antworten freigeben */
			semaphor.sem_op = 1;
                	semaphor.sem_flg = SEM_UNDO;

                	/* Freigeben einer Ressource */
                	if(semop(sem_antwortid, &semaphor, 1) == -1){
                        	fprintf(stderr, "Error: semaphore (Antworten) konnte nicht inkrementiert werden\n");
                        	exit(-1);
                	}

			sleep(1);
		}

	}

	/****************************** Aufraeumen *********************************************/

	/* Freigabe des Shared Memories fuer Anforderungen */
	if(shmdt((char *)shm_anford) == -1){
		fprintf(stderr, "Error: shared memory (Anforderungen) konnte nicht freigegeben werden\n");
		exit(-1);
	}

	/* Freigabe des Shared Memories fuer Antworten */
	if(shmdt((char *)shm_antwort) == -1){
		fprintf(stderr, "Error: shared memory (Antworten) konnte nicht freigegeben werden\n");
		exit(-1);
	}

	exit(0);
}

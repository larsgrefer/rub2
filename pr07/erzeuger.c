#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "sm.h"
#include "pv.h"

static int shm_anfordid,shm_antwortid;
static int sem_anfordid,sem_antwortid;
static struct sembuf semaphor;


int main(void)
{
	int neues_wort,client,i;
	anforder_shm	*shm_anford;
	antwort_shm 	*shm_antwort;
	char buf[MAX_LAENGE];

	/******************************** initialisieren *********************************/

	/* Anlegen des Shared Memories fuer Anforderungen */
	if((shm_anfordid = shmget(SHM_READKEY, MAX_LAENGE, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1){
		fprintf(stderr,"Error(%d): Anforderungs shared memory konnte nicht angelegt werden\n", shm_anfordid);
		exit(-1);
	}

	/* Anbinden des Shared Memories fuer Anforderungen */
	if((shm_anford = shmat(shm_anfordid, NULL, 0)) == (void*)-1){
		fprintf(stderr,"Error(%p): Anforderungs shared memory konnte nicht angebunden werden\n", shm_anford);
		exit(-1);
	}

	/* Anlegen des Shared Memories fuer Antworten */
	if((shm_antwortid = shmget(SHM_WRITEKEY, MAX_LAENGE, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1){
		fprintf(stderr,"Error(%d): Antwort shared memory konnte nicht angelegt werden\n", shm_antwortid);
		exit(-1);
	}

	/* Anbinden des Shared Memories fuer Antworten */
	if((shm_antwort = shmat(shm_antwortid, NULL, 0)) == (void*)-1){
		fprintf(stderr,"Error(%p): Antwort shared memory konnte nicht angebunden werden\n", shm_antwort);
		exit(-1);
	}

        /* Anlegen des Semaphors fuer Anforderungen */
        if((sem_anfordid = semget(SEM_READKEY, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1){
                fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht angelegt werden\n");
                exit(-1);
        }

        /* Setzen des Sempahors fuer Anforderungen auf 1 */
        if(semctl(sem_anfordid, 0, SETVAL, (int)1) == -1){
                fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht gesetzt werden\n");
                exit(-1);
        }

        /* Anlegen des Semaphors fuer Antworten */
        if((sem_antwortid = semget(SEM_WRITEKEY, 1, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1){
                fprintf(stderr,"Error: semaphore (Antworten) konnte nicht angelegt werden\n");
                exit(-1);
        }

        /* Setzen des Sempahors fuer Antworten auf 1 */
        if(semctl(sem_antwortid, 0, SETVAL, (int)1) == -1){
                fprintf(stderr,"Error: semaphore (Antworten) konnte nicht gesetzt werden\n");
                exit(-1);
        }

	/****************************** Sammeln und Rechnen ************************************/

	while(1)
	{
		neues_wort=0;

		/* Semaphor fuer Anforderungen setzen */
		semaphor.sem_op = -1;
                semaphor.sem_flg = SEM_UNDO;

                /* Anfordern einer Ressource */
                if(semop(sem_anfordid , &semaphor, 1) == -1){
                        fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht dekrementiert werden\n");
                        exit(-1);
                }

		if(shm_anford->ungelesen){
			strcpy(buf, shm_anford->text);
			client = client + 1;
			neues_wort = 1;
			shm_anford->ungelesen = 0;
		}

		/* Abbruchkriterium client = 1000 SHM_MAXSAETZE aus sm.h */
		if(client == SHM_MAXSAETZE){ 
			sleep(1);
			break;
		}
		
		/* Semaphor fuer Anforderungen freigeben */
		semaphor.sem_op = 1;
                semaphor.sem_flg = SEM_UNDO;

                /* Freigeben einer Ressource */
                if(semop(sem_anfordid, &semaphor, 1) == -1){
                        fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht inkrementiert werden\n");
                        exit(-1);
                }

		if(neues_wort){
			for(i=0; i < strlen(buf); i++)
				buf[i] = toupper(buf[i]);
			buf[i] = '\0';

   			/* Semaphor fuer Antworten setzen */
			semaphor.sem_op = -1;
                	semaphor.sem_flg = SEM_UNDO;

                	/* Anfordern einer Ressource */
                	if(semop(sem_antwortid, &semaphor, 1) == -1){
                        	fprintf(stderr,"Error: semaphore (Antworten) konnte nicht dekrementiert werden\n");
                        	exit(-1);
                	}

			shm_antwort->ungelesen = 1;
			strcpy(shm_antwort->ergebnis, buf);
			shm_antwort->client_nr = shm_anford->client_nr;
	
			/* Semaphor fuer Antworten freigeben */
			semaphor.sem_op = 1;
                	semaphor.sem_flg = SEM_UNDO;

                	/* Freigeben einer Ressource */
                	if(semop(sem_antwortid, &semaphor, 1) == -1){
                        	fprintf(stderr,"Error: semaphore (Antworten) konnte nicht inkrementiert werden\n");
                        	exit(-1);
                	}
		}
		else
		  	sleep(2);

	}

	/****************************** Aufraeumen *********************************************/

       	/* Loeschen des Sempahors fuer Anforderungen */
        if(semctl(sem_anfordid, 0, IPC_RMID) == -1){
                fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht geloescht werden\n");
                exit(-1);
        }

       	/* Loeschen des Sempahors fuer Antworten */
        if(semctl(sem_antwortid, 0, IPC_RMID) == -1){
                fprintf(stderr,"Error: semaphore (Antworten) konnte nicht geloescht werden\n");
                exit(-1);
        }

	/* Freigabe des Shared Memories fuer Anforderungen */
	if(shmdt((char *)shm_anford) == -1){
		fprintf(stderr,"Error: shared memory (Anforderungen) konnte nicht freigegeben werden\n");
		exit(-1);
	}

	/* Freigabe des Shared Memories fuer Antworten */
	if(shmdt((char *)shm_antwort) == -1){
		fprintf(stderr,"Error: shared memory (Antworten) konnte nicht freigegeben werden\n");
		exit(-1);
	}

	/* Loeschen des des Shared Memories fuer Anforderungen */
	if(shmctl(shm_anfordid, IPC_RMID, NULL) == -1){
		fprintf(stderr,"Error: shared memory (Anforderungen) konnte nicht geloescht werden\n");
		exit(-1);
	}

	/* Loeschen des des Shared Memories fuer Antworten */
	if(shmctl(shm_antwortid, IPC_RMID, NULL) == -1){
		fprintf(stderr,"Error: shared memory (Antworten) konnte nicht geloescht werden\n");
		exit(-1);
	}
	

	exit(0);
}

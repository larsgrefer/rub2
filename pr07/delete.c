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

int main(void){
  
	/* Anlegen des Shared Memories fuer Anforderungen */
	if((shm_anfordid = shmget(SHM_READKEY, MAX_LAENGE, 0)) == -1){
		fprintf(stdout,"Anforderungs shared memory nicht vorhanden\n");
	}else
	/* Loeschen des des Shared Memories fuer Anforderungen */
	if(shmctl(shm_anfordid, IPC_RMID, NULL) == -1){
		fprintf(stderr,"Error: shared memory (Anforderungen) konnte nicht geloescht werden\n");
	}else{
                fprintf(stdout,"Anforderungs shared memory entfernt\n");
	}




	/* Anlegen des Shared Memories fuer Antworten */
	if((shm_antwortid = shmget(SHM_WRITEKEY, MAX_LAENGE, 0)) == -1){
		fprintf(stdout,"Antwort shared memory nicht vorhanden\n");
	}else
	/* Loeschen des des Shared Memories fuer Antworten */
	if(shmctl(shm_antwortid, IPC_RMID, NULL) == -1){
		fprintf(stderr,"Error: shared memory (Antworten) konnte nicht geloescht werden\n");
	}else{
                fprintf(stdout,"Antwort shared memory entfernt\n");
	}




	/* Anlegen des Semaphors fuer Anforderungen */
        if((sem_anfordid = semget(SEM_READKEY, 0, 0)) == -1){
                fprintf(stdout,"Semaphore (Anforderungen) nicht vorhanden\n");               
        }else
         /* Loeschen des Sempahors fuer Anforderungen */
        if(semctl(sem_anfordid, 0, IPC_RMID) == -1){
                fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht geloescht werden\n");
        }else{
                fprintf(stdout,"Semaphore (Anforderungen) entfernt\n");
	}
        
        
        
        /* Anlegen des Semaphors fuer Antworten */
        if((sem_antwortid = semget(SEM_WRITEKEY, 0, 0)) == -1){
                fprintf(stdout,"Semaphore (Antworten) nicht vorhanden\n");
        }else
        /* Loeschen des Sempahors fuer Antworten */
        if(semctl(sem_antwortid, 0, IPC_RMID) == -1){
                fprintf(stderr,"Error: semaphore (Antworten) konnte nicht geloescht werden\n");   
        }else{
                fprintf(stdout,"Semaphore (Antworten) entfernt\n");
	}

	
	fprintf(stdout, "\n\nAufraumen abgeschlossen.\n\n");

	exit(0);
  
}

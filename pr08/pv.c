#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "sm.h"

#include <errno.h>
#include <fcntl.h>

/* 
 * Anlegen neuen Semaphors fuer Anforderungen mit dem Schluessel key 
 * Rückgabe ist eine ID
 */

int sem_create(key_t key)
{
  int sem_anfordid;

  if((sem_anfordid=semget(key,1,S_IRWXU|S_IRWXG|S_IRWXO|IPC_CREAT|IPC_EXCL))==-1)
    {
      fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht angelegt werden\n");
      exit(-1);
    }
  return (sem_anfordid);
}

/* 
 * Verbinden eines bereits existierenden Semaphors mit dem Schluessel key 
 * Rückgabe ist eine ID
 */

int sem_connect(key_t key)
{
  int sem_anfordid;

  if((sem_anfordid=semget(key,0,0))==-1)
    {
      fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht angelegt werden\n");
      exit(-1);
    }
  return (sem_anfordid);
}

/* 
 * Setzen des Sempahors mit der ID id value 
 */

int sem_set(int id, int value)
{
  if(semctl(id,0,SETVAL,(int)value)==-1)
    {
      fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht gesetzt werden\n");
      exit(-1);
    }
  return(0);
}

/* 
 * Abfragen des Wertes des Sempahors mit der ID id  
 */

int sem_get(int id)
{
	int rval;

	if((rval=semctl(id,0,GETVAL,NULL))==-1){
		fprintf(stderr,"Error: semaphore konnte nicht gelesen werden\n");
		exit(-1);
	}
	return rval;

}

/* 
 * Semaphore mit der ID id löschen
 */

void sem_rm(int id)
{
  if(semctl(id,0,IPC_RMID,(int)0)==-1)
    {
      fprintf(stderr,"Error: semaphore (Anforderungen) konnte nicht geloescht werden\n");
      exit(-1);
    }
}


void pv(int id, int operation)
{
   static struct sembuf semaphor;

   semaphor.sem_num = 0;
   semaphor.sem_op  = operation;
   semaphor.sem_flg = 0;

   if (semop(id, &semaphor, 1) == -1)
      perror("semop-Fehler");
}







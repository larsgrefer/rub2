#include  <sys/ipc.h>
#include  <sys/sem.h>
#include  "pv.h"

void pv(int id, int operation)
{
   static struct sembuf   semaphor;

   semaphor.sem_op  = operation;
   semaphor.sem_flg = SEM_UNDO;

   if (semop(id, &semaphor, 1) == -1)
      perror("semop-Fehler");
}

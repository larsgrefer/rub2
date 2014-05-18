#ifndef  PV
#define  PV

/*---- Makros fuer die P- und V-Operationen -------------*/
#define  P(id)  pv(id, -1)
#define  V(id)  pv(id, 1)

extern void pv(int id, int operation);

#endif

int sem_create(key_t key);
int sem_connect(key_t key);
int sem_set(int id, int value);
int sem_get(int id);
int sem_rm(int id);



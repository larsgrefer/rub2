#ifndef  PV
#define  PV

/*---- Makros fuer die P- und V-Operationen -------------*/
#define  P(id)  pv(id, -1)
#define  V(id)  pv(id, 1)

extern void pv(int id, int operation);

#endif

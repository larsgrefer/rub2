#ifndef SM
#define SM

/* vereinbart Schluessel zwischen Server und Clients */
#define SHM_READKEY 10001
#define SHM_WRITEKEY 10002
#define SEM_READKEY 20001
#define SEM_WRITEKEY 20002

/* maximale Laenge einer Nachricht */
#define MAX_LAENGE 200
#define SHM_MAXSAETZE 1000

/* Datentypen fuer Client-Anforderung und Server-Antwort */
typedef struct {
	int	client_nr;
	char	text[MAX_LAENGE];
	char 	ungelesen;	
} anforder_shm;

typedef struct {
	int	client_nr;
	char	ergebnis[MAX_LAENGE];
	char 	ungelesen;	
} antwort_shm;


#endif

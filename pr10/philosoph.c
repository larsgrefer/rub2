#include <pthread.h>
#include <stdio.h>
#define NR_OF_PHIL 5

static int gabel_vorhanden[NR_OF_PHIL],rechts[NR_OF_PHIL],links[NR_OF_PHIL]; 
                mutex=                ;

void *phil(void *arg);

int main (void)
{
	int i,status;
	pthread_t thread[NR_OF_PHIL];

	init_gabeln(NR_OF_PHIL);

	/* Starte die Threads */
	for(i=0;i<NR_OF_PHIL;i++){
		status=              (                     );
		if(status!=0){
			fprintf(stderr,"Error: Konnte Thread %d nicht erzeugen\n",i);
			exit(-1);		
		}
	}

	/* Warte auf Terminierung */
	for(i=0;i<NR_OF_PHIL;i++)
		              (thread[i],NULL);

	exit(0);
}

void *phil(void *arg){

	int nr = (int)arg;
	int i;

	printf("Philosoph %d gestartet\n",nr);

	for(i=0;i<20;i++)
	{
		 
		printf("Philosoph %d isst\n",nr);
		sleep(nr/2);
		 
		sleep(1);
	}

	printf("Philosoph %d ist fertig\n",nr);

	return NULL;
}

int gabeln_holen(int i){

	int erfolg=0;

	 
	
	return erfolg;
}

void gabeln_abgeben(int i){

 
}

void init_gabeln(int nr){

	int i;

	for(i=0;i<nr;i++){
		gabel_vorhanden[i]=2;
		rechts[i]=(i+1)%nr;
		links[i]=(i-1+nr)%nr;
	}
}

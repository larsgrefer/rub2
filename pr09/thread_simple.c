#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *schlafe(void *arg);
void sleep_thread_new(pthread_t *thread, int sleeptime);

int main (int argc, char *argv[])
{
	int number_of_threads = argc -1;
	int i;

	int sleeptime[number_of_threads];
	pthread_t thread[number_of_threads];

	/* Lese Schlafzeiten ein */
	if(number_of_threads < 1){
		printf("Bitte mindestens eine Zeit eingeben.\n\tUsage: Thread time1 [time...]\n");
		exit(-1);
	}else{
		printf("Erstelle %d Threads\n\n", number_of_threads);
	}

	for(i = 0; i < number_of_threads; i++){
		sleeptime[i] = atoi(argv[i + 1]);
	}


	/* Starte die Threads */
	for(i = 0; i < number_of_threads; i++){
		sleep_thread_new(&thread[i], sleeptime[i]);
	}


	/* Warte auf Terminierungen */
	for(i = 0; i < number_of_threads; i++){
		pthread_join(thread[i], NULL);
	}

	exit(0);
}

void sleep_thread_new(pthread_t *thread, int sleeptime){
	int err = pthread_create(thread, NULL, schlafe, (int*)sleeptime);
	if(err != 0){
		fprintf(stderr, "Fehler beim erstellen von Thread: Fehler(%d)\n", err);
		exit(-1);
	}

}

void *schlafe(void *arg){

	int sleeptime = (int)arg;

	printf("Thread wird gestartet, warte %d Millisekunden\n", sleeptime);

	int time = 0;
	while(time < sleeptime)
	{
		time++;
		int err = nanosleep((struct timespec[]){{0, 1000000}}, NULL);
		if(err < 0)
		{
			printf("Fehler beim schlafen \n");
			exit(-1);
		}
	}
	//sleep(sleeptime);

	printf("Fertig mit warten von %d Milliekunden\n", sleeptime);

	return NULL;
}

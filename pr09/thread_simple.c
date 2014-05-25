#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
		printf("Error: Es wird mindestens eine Schlafzeit erwartet.\n");
		exit(-1);
	}else{
		printf("Versuche %d Threads zu erstellen.\n\n", number_of_threads);
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

	if(pthread_create(thread, NULL, schlafe, (int*)sleeptime) != 0){
		fprintf(stderr, "Error: Konnte Thread nicht erzeugen\n");
		exit(-1);
	}

}

void *schlafe(void *arg){

	int sleeptime = (int)arg;

	printf("Thread(%d) wird gestartet\n", sleeptime);

	sleep(sleeptime);

	printf("Thread(%d) wird beendet\n", sleeptime);

	return NULL;
}

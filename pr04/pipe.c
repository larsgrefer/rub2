#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXLINE 4096

void toUpperCase(char*);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Es wird ein Argument erwartet.\n");
		return EXIT_SUCCESS;
	}
	int n /*Number of chars read*/, A[2] /*Parent -> Child*/,
			B[2]/*Child -> Parent*/, err;
	pid_t pid;
	char line[MAXLINE];	//Buffer

	err = pipe(A); //Erzeugen der ersten Pipe
	if (err < 0) {
		perror("pipe error");
		exit(1);
	}

	err = pipe(B); //Erzeugen der zweiten Pipe
	if (err < 0) {
		perror("pipe error");
		exit(1);
	}

	pid = fork(); //Erzeugen des Kindprozesses
	if (pid < 0) {
		perror("fork error");
		exit(1);
	} else if (pid > 0) { /* parent */
		close(A[0]);			//Lesezugriff auf Pipe A schließen
		close(B[1]);			//Schreibzugriff auf Pipe B schließen
		char *argument = argv[1];
		write(A[1], argument, strlen(argument)); //Text an das Kind senden
		close(A[1]);			//Schreibzugriff auf Pipe A schließen
		n = read(B[0], line, MAXLINE); //Aus Pipe B lesen
		close(B[0]);			//Lesezugriff auf Pipe B schließen
		write(STDOUT_FILENO, line, n); //Gelesenen Text auf die Konsole schreiben
		printf("\n");
		waitpid(pid, NULL, 0);	//Warte auf Beendigung des Kindes
	} else {/* child */
		close(A[1]);			//Schreibzugriff auf Pipe A schließen
		close(B[0]);			//Lesezuggriff auf Pipe B schließen
		n = read(A[0], line, MAXLINE);	//Aus Pipe A lesen
		close(A[0]);			//Lesezugriff auf Pipe A schließen
		sleep(1);				//Einen kurzen Moment warten
		toUpperCase(line);		//Input in Großbuchstabe umwandeln
		write(B[1], line, n);	//Gelesenen Text zurück an den Parent senden
		close(B[1]);			//Schreibezugriff auf Pipe B schließen
	}
	return EXIT_SUCCESS;
}

void toUpperCase(char *string) {
	while (*(string) != '\0') {
		*string = toupper(*string);
		string += sizeof(char);
	}
}

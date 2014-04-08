#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char * argv[]) {

	int fd[2];

	if (pipe(fd) == 0) {

		printf("fd[0]=%d\n", fd[0]);
		printf("fd[1]=%d\n", fd[1]);

		char *text = "Irgendein Text\n"; //Text, der in die Pipe geschrieben wird

		int write_ret = write(fd[1], text, strlen(text)); //Text in die Pipe schreiben
		if (write_ret == -1) {
			perror("Fehler beim Schreiben in die Pipe");
		} else {
			printf("%d Zeichen geschrieben.\n", write_ret);
		}
		close(fd[1]);	//OutputStream schließen

		printf("\nLese aus der Pipe ...\n");

		char buf[51];	//Lese-Buffer

		int read_ret;	//Anzahl gelesener Zeichen
		while ((read_ret = read(fd[0], buf, 50)) > 0) {
			//Solange kein Error oder EoF auftritt in Buffer lesen
			buf[read_ret] = '\0';//Hinter dem letzten gelesenen Zeichen String Terminator einfügen
			printf("%s", buf);	//So weit gelesenen Text ausgeben
		}

		if (read_ret == -1) {
			perror("Fehler beim Lesen der Pipe");
		}

		close(fd[0]);	//InputStream schließen
	} else {
		perror("Fehler beim Erzeugen der Pipe");
	}
	return EXIT_SUCCESS;
}

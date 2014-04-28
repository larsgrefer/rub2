#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

#define BUFFERSIZE 1024

void arrayToUpper(char*, int);
void printArray(char*, int);

int main(int argc, char* argv[]){

	int fd_in = STDIN_FILENO; //File descriptor um aus der Standarteingabe lesen zu können

	ssize_t num_read; //Anzahl gelesener Zeichen
	char buf[BUFFERSIZE]; //Buffer für die gelesenen Zeichen
	
	while((num_read = read(fd_in, buf, BUFFERSIZE)) > 0){ //Lese solange kein Fehler autritt oder der Stream endet
		arrayToUpper(buf, num_read); //Konvertiere zu Großbuchstaben
		printArray(buf, num_read); //Schreibe auf die Standartausgabe
	}

	return EXIT_SUCCESS;
}

void arrayToUpper(char *array, int len){

	int i;
	for(i = 0; i < len; i++){
		array[i] = toupper(array[i]);
	}

}

void printArray(char *array, int len){
	
	write(STDOUT_FILENO, array, len);

}

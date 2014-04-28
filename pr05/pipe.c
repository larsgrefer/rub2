#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define MAXLINE 4096

int main(int argc, char* argv[]) {

  if(argc < 2){
  	printf("Es wird mindestens ein Argument erwartet.\n");
  	return EXIT_SUCCESS;
  }
  
  int   n/*Number of chars read*/, A[2]/*Parent -> Child*/, B[2]/*Child -> Parent*/, err;
  pid_t pid;
  char  line[MAXLINE]; //Buffer
  
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
  }     
  else if (pid > 0) {           /* parent */
    close(A[0]); //Lesezugriff auf Pipe A schließen
    close(B[1]); //Schreibzugriff auf Pipe B schließen
    
    char space[1];
    space[0] = ' ';
    
    int i;
    for(i = 1; i < argc; i++){
	    char *argument = argv[i];
	    write(A[1], argument, strlen(argument)); //Text an das Kind senden
	    write(A[1], space, 1); //Leerzeichen als Argumenttrennzeichen
    }
    
    close(A[1]); //Schreibzugriff auf Pipe A schließen
    
    while((n = read(B[0], line, MAXLINE)) > 0){ //Aus Pipe B lesen
    	write(STDOUT_FILENO, line, n); //Gelesenen Text auf die Konsole schreiben
    }
    close(B[0]); //Lesezugriff auf Pipe B schließen
    
    printf("\n");
    waitpid(pid, NULL, 0); //Warte auf Beendigung des Kindes
  }
  else {                        /* child */
    close(A[1]); //Schreibzugriff auf Pipe A schließen
    close(B[0]); //Lesezuggriff auf Pipe B schließen
    
    dup2(A[0], STDIN_FILENO); //Output des parent auf input umbiegen
    dup2(B[1], STDOUT_FILENO); //Input des parent auf ouput umbiegen
    
    int err = execlp("./filter", "./filter", NULL);
    if(err == -1){
    	perror("exec filter error");
    }
  }
  

  return EXIT_SUCCESS;
}

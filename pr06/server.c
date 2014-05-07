#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define BUFFERSIZE 512

const char fifo_A[] = "/tmp/fifo_A"; // FIFO aus der gelesen wird
const char fifo_B[] = "/tmp/fifo_B"; // FIFO in die geschrieben wird

void createfifo(const char*);
void sighandler(int);
int openfile(const char*, int);
bool closefile(int);
void streamtoupper(const int, const int);
void arrayToUpper(char*, int);


int main(int argc, char* argv[]){

  printf("Erstelle FIFOs und Signalhandler\n");
  createfifo(fifo_A); // FIFO A erstellen
  createfifo(fifo_B); // FIFO B erstellen

  signal(SIGINT, sighandler); // Signal-handler, um im Fall der Beendigung
  signal(SIGTERM, sighandler); //  die FIFO's löschen zu können
  
  int fd_A; // File descriptor A
  int fd_B; // File descriptor B
  
  while(TRUE){
    
    printf("FIFOs öffnen\n");
    fd_A = openfile(fifo_A, O_RDONLY); // FIFO A öffnen
    fd_B = openfile(fifo_B, O_WRONLY); // FIFO B öffnen    
    
    streamtoupper(fd_A, fd_B); // FIFO A lesen, umwandeln und in FIFO B schreiben
    
    printf("FIFOs schließen\n");
    if(closefile(fd_A) || closefile(fd_B)){ // FIFO's schließen und bei Fehler beenden
     exit(-1);
    }
    
  }
  
  return EXIT_SUCCESS;
}



void streamtoupper(const int fd_in, const int fd_out){
  printf("Umwandeln...\n");
  
  ssize_t num, num2;
  char buf[BUFFERSIZE];
  
  while((num = read(fd_in, buf, BUFFERSIZE)) > 0){
    printf("<- %d\n", (int)num);
    arrayToUpper(buf, num);
    
    if((num2 = write(fd_out, buf, num)) == -1){
      perror("Error streamtoupper write");
    }else{
     printf("%d ->\n", (int)num2); 
    }
    break;
  }
  
  if(num == -1){
    perror("Error streamtoupper read");
  }
  
}


void arrayToUpper(char *array, int len){

  int i;
  for(i = 0; i < len; i++){
    array[i] = toupper(array[i]);
  }

}

bool closefile(int fd){
  bool err = FALSE;
  
  if(close(fd) == -1){
    err = TRUE;
  }
  
  return err;
}

int openfile(const char *path, int flags){
 
  int ret = open(path, flags);
  if(ret == -1){
    perror("Error openfile");
    exit(-1);
  }
  
  return ret;
}

void createfifo(const char *path){

  int ret = mkfifo(path, 0664);
  if(ret == -1){
    perror("Error create fifo");
    exit(-1);
  }
  
}

void sighandler(int nr){
  if(nr == SIGINT || nr == SIGTERM){
    if(unlink(fifo_A) == -1){
      perror("Error clean");
    }
    if(unlink(fifo_B) == -1){
     perror("Error clean"); 
    }
    exit(0);
  }
}

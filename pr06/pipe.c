#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFERSIZE 512

const char fifo_A[] = "/tmp/fifo_A"; // FIFO aus der gelesen wird
const char fifo_B[] = "/tmp/fifo_B"; // FIFO in die geschrieben wird

int openfile(const char*, int);
void convert(const char*);

int main(int argc, char* argv[]) {

  if(argc < 2){
    printf("Es wird mindestens ein Argument erwartet\n");
  }
  
  int i;
  for(i = 1; i < argc; i++){
    printf("Konvertiere Argument %d\n", i);   
    
    convert(argv[i]);
    
  }
  
  return EXIT_SUCCESS;
}

void convert(const char *arg){
 
  pid_t pid = fork();
  
  if(pid == 0){
  
    // LESEN
    
    printf("Öffne FIFO B\n");
    int fd_B = openfile(fifo_B, O_RDONLY);
  
      
    ssize_t num;
    char buf[BUFFERSIZE];
    buf[BUFFERSIZE - 1] = '\0';
    
    printf("Lese ...\n");
    while((num = read(fd_B, buf, (BUFFERSIZE - 1))) > 0){
      buf[num] = '\0';
      printf("<- %s\n", buf);
    }
    
    if(num == -1){
      perror("Error convert read");
    }
      
    if(close(fd_B) == -1){
      perror("Error close fd_B"); 
    }
    
    exit(0);
    //LESEN
    
  }else if(pid > 0){
  
    //SCHREIBEN
    
    printf("Öffne FIFO A\n");
    int fd_A = openfile(fifo_A, O_WRONLY);
  
    printf("%s ->\n", arg);
    if(write(fd_A, arg, strlen(arg)) == -1){ // Argument schreiben
      perror("Error write argument");
      exit(-1);
    }
    
    if(close(fd_A) == -1){
      perror("Error close fd_A"); 
    }
    
    //SCHREIBEN
    printf("Warte auf Kind\n");
    waitpid(pid, NULL, 0);
    printf("Fertig\n");
    
  }else if(pid == -1){
    perror("Error fork");
  }
  
}

int openfile(const char *path, int flags){
 
  int ret = open(path, flags);
  if(ret == -1){
    perror("Error openfile");
    exit(-1);
  }
  
  return ret;
}
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#define MAXLINE 4096

int main(void) {
  int   n, fd[2], err;
  pid_t pid;
  char  line[MAXLINE];
  
  err = pipe(fd);
  if (err < 0) {
    perror("pipe error");
    exit(1);
  }     

  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(1);
  }     
  
  else if (pid > 0) {           /* parent */
    close(fd[0]);
    write(fd[1], "hello world\n", 12);
    
  } 
  else {                        /* child */
    close(fd[1]);
    n = read(fd[0], line, MAXLINE);
    write(STDOUT_FILENO, line, n);
  }
  wait(NULL);
  return 0;
}

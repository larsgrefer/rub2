#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 

#define MAXLINE 4096	/* max line length */

static void	sig_usr(int);

int main(void) {
  char	buf[MAXLINE];
  pid_t   pid;
  int		status;
  
  if (signal(SIGINT, sig_usr) == SIG_ERR)
      perror("kann SIGINT nicht abfangen");
    if (signal(SIGTERM, sig_usr) == SIG_ERR)
      perror("kann SIGTERM nicht abfangen");

  printf("%% ");  /* print prompt (printf requires %% to print %) */
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    buf[strlen(buf) - 1] = 0;	/* replace newline with null */
    if(strlen(buf) == 1)
    {
    	if(buf[0] == 'q')
    		exit(0);
    }
    else if ( (pid = fork()) < 0)
      perror("fork error");
    
    else if (pid == 0) {		/* child */
      execlp(buf, buf, (char *) 0);
      printf("couldn't execute: %s\n", buf); 
      exit(127);
    }

    /* parent */
    if ( (pid = waitpid(pid, &status, 0)) < 0)
      perror("waitpid error"); 
    printf("%% ");
  }
  exit(0);
}

static void sig_usr(int signo)		/* Argument ist Signalnummer */
{
  if (signo == SIGTERM)
    printf("sig_usr: SIGTERM abgefangen\n");
  else if (signo == SIGINT)
    printf("sig_usr: SIGINT abgefangen\n");

  return;
}


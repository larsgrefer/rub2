/*
 * suizid2.c
 *
 *  Created on: 02.04.2014
 *      Author: larsgrefer
 */


#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

static void sig_usr(int);

int main(void)
{
	if (signal(SIGINT, sig_usr) == SIG_ERR)
	    perror("kann SIGINT nicht abfangen");


	kill(getpid(), SIGINT);
	printf("Ich lebe noch\n");
	sleep(2);
	return 0;
}

static void sig_usr(int signo)		/* Argument ist Signalnummer */
{
  if (signo == SIGINT)
    printf("sig_usr: SIGINT abgefangen\n");

  return;
}

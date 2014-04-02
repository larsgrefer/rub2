/*
 * suizid.c
 *
 *  Created on: 02.04.2014
 *      Author: larsgrefer
 */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	kill(getpid(), SIGINT);
	printf("Ich lebe noch");
	sleep(2);
	return 0;
}
